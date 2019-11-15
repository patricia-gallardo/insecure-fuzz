# Trying to fuzz OpenSSL for HeartBleed

Based on https://google.github.io/clusterfuzz/setting-up-fuzzing/heartbleed-example/

Install AFL

~~~~bash
sudo apt install afl afl-clang afl-cov afl-doc
~~~~

Install dependencies

~~~~bash

~~~~

Get the Code

~~~~bash
curl -O https://www.openssl.org/source/openssl-1.0.1f.tar.gz
tar xf openssl-1.0.1f.tar.gz
~~~~

Build

~~~~bash
cd openssl-1.0.1f/

export AFL_USE_ASAN=1
export CC=/usr/bin/afl-clang-fast
export CXX=/usr/bin/afl-clang-fast++
export AFL_INST_RATIO=100

./config && make
cd ..
~~~~

Get Fuzz Target

~~~~bash
curl -O https://raw.githubusercontent.com/patricia-gallardo/insecure-fuzz/master/fuzz_targets/open_ssl_heartbleed/handshake-fuzzer.cc
curl -O https://raw.githubusercontent.com/patricia-gallardo/insecure-fuzz/master/fuzz_targets/open_ssl_heartbleed/server.key
curl -O https://raw.githubusercontent.com/patricia-gallardo/insecure-fuzz/master/fuzz_targets/open_ssl_heartbleed/server.pem
~~~~

Build Fuzz Target

~~~~bash
$CXX -g handshake-fuzzer.cc openssl-1.0.1f/libssl.a openssl-1.0.1f/libcrypto.a -std=c++14 -Iopenssl-1.0.1f/include/ -lstdc++fs -ldl -lstdc++ -o handshake-fuzzer
~~~~

Set up Initial Corpus and Output directories

~~~~bash
mkdir afl_corpus afl_output
echo "-" > afl_corpus/test.txt
~~~~

Run AFL

~~~~bash
afl-fuzz -m none -i afl_corpus/ -o afl_output/ ./handshake-fuzzer @@
~~~~

Reproduce crash

~~~~bash
./handshake-fuzzer afl_output/crashes/<file>
~~~~

Sample output

~~~~bash
==13465==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x629000009748 at pc 0x0000004beec1 bp 0x7ffd1ee4cfb0 sp 0x7ffd1ee4c760
~~~~
