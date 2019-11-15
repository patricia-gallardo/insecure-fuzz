// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Original version written by Kostya Serebryany.
// Rewritten for AFL by Patricia Aas
//

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string>

#ifdef __cpp_lib_filesystem
#include <filesystem>
static std::filesystem::path filepath;
#else

#include <experimental/filesystem>

static std::experimental::filesystem::path filepath;
#endif

static SSL_CTX *sctx;

class Environment {
public:
  Environment(std::string program) {
    filepath = program;
    SSL_library_init();
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();
    assert(sctx = SSL_CTX_new(TLSv1_method()));
    filepath.replace_filename("server.pem");
    assert(SSL_CTX_use_certificate_file(sctx, filepath.c_str(),
                                        SSL_FILETYPE_PEM));
    filepath.replace_filename("server.key");
    assert(SSL_CTX_use_PrivateKey_file(sctx, filepath.c_str(),
                                       SSL_FILETYPE_PEM));
  }
};

int readFile(char *filename, uint8_t **buffer, size_t *buffer_size) {
  char *source = NULL;
  FILE *fp = fopen(filename, "r");
  if (fp == NULL)
    return false;

  if (fseek(fp, 0L, SEEK_END) != 0)
    return false;

  long bufsize = ftell(fp);
  if (bufsize == -1)
    return false;

  *buffer_size = bufsize;

  source = (char *) malloc(sizeof(char) * (bufsize));

  if (fseek(fp, 0L, SEEK_SET) != 0)
    return false;

  size_t newLen = fread(source, sizeof(char), bufsize, fp);
  if (ferror(fp) != 0)
    return false;

  fclose(fp);
  *buffer = (uint8_t *) source;
  return true;
}

int main(int argc, char **argv) {
  static Environment env(argv[0]);

  uint8_t *buffer;
  size_t buffer_size;
  if (!readFile(argv[1], &buffer, &buffer_size))
    exit(EXIT_FAILURE);

  SSL *server = SSL_new(sctx);
  BIO *sinbio = BIO_new(BIO_s_mem());
  BIO *soutbio = BIO_new(BIO_s_mem());
  SSL_set_bio(server, sinbio, soutbio);
  SSL_set_accept_state(server);
  BIO_write(sinbio, buffer, buffer_size);
  SSL_do_handshake(server);
  SSL_free(server);

  free(buffer);
  return EXIT_SUCCESS;
}