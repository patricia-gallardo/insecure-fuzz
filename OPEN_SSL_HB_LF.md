# Trying to fuzz OpenSSL for HeartBleed with libFuzzer

Based on https://google.github.io/clusterfuzz/setting-up-fuzzing/heartbleed-example/

Install Clang

~~~~bash
sudo apt install clang
~~~~

Install dependencies

~~~~bash

~~~~

Get the Code to be Fuzzed

~~~~bash
curl -O https://www.openssl.org/source/openssl-1.0.1f.tar.gz
tar xf openssl-1.0.1f.tar.gz
~~~~

Build

~~~~bash
cd openssl-1.0.1f/
./config && make CC="clang -g -fsanitize=address,fuzzer-no-link" && cd ..
~~~~

Get Fuzz Target

~~~~bash
curl -O https://raw.githubusercontent.com/patricia-gallardo/insecure-fuzz/master/fuzz_targets/open_ssl_heartbleed/lib_fuzzer_handshake_fuzzer.cc
curl -O https://raw.githubusercontent.com/patricia-gallardo/insecure-fuzz/master/fuzz_targets/open_ssl_heartbleed/server.key
curl -O https://raw.githubusercontent.com/patricia-gallardo/insecure-fuzz/master/fuzz_targets/open_ssl_heartbleed/server.pem
~~~~

Build Fuzz Target

~~~~bash
clang++ -g lib_fuzzer_handshake_fuzzer.cc -fsanitize=address,fuzzer openssl-1.0.1f/libssl.a openssl-1.0.1f/libcrypto.a -std=c++14 -Iopenssl-1.0.1f/include/ -lstdc++fs -ldl -lstdc++ -o lib_fuzzer_handshake_fuzzer
~~~~

Set up Initial Corpus

~~~~bash
mkdir lf_corpus
echo "-" > lf_corpus/test.txt
~~~~

Run libFuzzer

~~~~bash
./lib_fuzzer_handshake_fuzzer lf_corpus
~~~~

Reproduce crash

~~~~bash
~~~~

Sample output

~~~~bash
==15058==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x629000009748 at pc 0x000000512be2 bp 0x7ffcbdf3c460 sp 0x7ffcbdf3bc10
READ of size 21761 at 0x629000009748 thread T0
~~~~
