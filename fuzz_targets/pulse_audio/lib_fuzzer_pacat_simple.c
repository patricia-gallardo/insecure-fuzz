/***
  This file is part of PulseAudio.
  PulseAudio is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published
  by the Free Software Foundation; either version 2.1 of the License,
  or (at your option) any later version.
  PulseAudio is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.
  You should have received a copy of the GNU Lesser General Public License
  along with PulseAudio; if not, see <http://www.gnu.org/licenses/>.
***/
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <pulse/simple.h>
#include <pulse/error.h>
#include <stdlib.h>

static pa_simple *s = NULL;

int LLVMFuzzerInitialize(const int* argc, char*** argv) {
  /* The Sample format to use */
  static const pa_sample_spec ss = {
      .format = PA_SAMPLE_S16LE,
      .rate = 44100,
      .channels = 2
  };
  int error;
  int ret = EXIT_SUCCESS;
  /* replace STDIN with the specified file if needed */
  if (*argc > 1) {
    int fd;
    if ((fd = open(*argv[1], O_RDONLY)) < 0) {
      fprintf(stderr, __FILE__": open() failed: %s\n", strerror(errno));
      ret = EXIT_FAILURE;
      goto finish;
    }
    if (dup2(fd, STDIN_FILENO) < 0) {
      fprintf(stderr, __FILE__": dup2() failed: %s\n", strerror(errno));
      ret = EXIT_FAILURE;
      goto finish;
    }
    close(fd);
  }
  /* Create a new playback stream */
  if (!(s = pa_simple_new(NULL, *argv[0], PA_STREAM_PLAYBACK, NULL, "playback", &ss, NULL, NULL, &error))) {
    fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
      ret = EXIT_FAILURE;
    goto finish;
  }
  finish:
  return ret;
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  int error;
  int ret = pa_simple_write(s, Data, Size, &error);
  return ret;
}
