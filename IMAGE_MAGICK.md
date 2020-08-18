# Trying to fuzz ImageMagick

* [CVE-2019-9956: stack-based buffer overflow](https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2019-9956)
* [GitHub Issue 1523](https://github.com/ImageMagick/ImageMagick/issues/1523)

Install AFL

~~~~bash
sudo apt install afl afl-clang afl-cov afl-doc
~~~~

Install dependencies

~~~~bash

~~~~

Get the Code to be Fuzzed

~~~~bash
git clone --branch 7.0.8-34 https://github.com/ImageMagick/ImageMagick.git
~~~~

Build

~~~~bash
cd ImageMagick

export AFL_USE_ASAN=1
export CC=/usr/bin/afl-gcc
export CXX=/usr/bin/afl-g++
export AFL_INST_RATIO=100

./configure --disable-shared && make && cd ..
~~~~

Get Fuzz Target

~~~~bash
~~~~

Build Fuzz Target

~~~~bash
~~~~

Set up Initial Corpus and Output directories

~~~~bash
mkdir afl_corpus afl_output
cp ./ImageMagick/PerlMagick/t/input.bmp afl_corpus/
~~~~

Run AFL

~~~~bash
export MAGICK_CONFIGURE_PATH="<path to checkout>/ImageMagick/config"
afl-fuzz -m none -i afl_corpus/ -o afl_output/ ./ImageMagick/utilities/magick convert @@ output.ps
~~~~

Reproduce crash

~~~~bash
./ImageMagick/utilities/magick convert afl_output/crashes/<file> output.ps
~~~~

Testing with file from report

~~~~bash
curl -O https://raw.githubusercontent.com/patricia-gallardo/insecure-fuzz/master/fuzz_targets/image_magick/test.file
./ImageMagick/utilities/magick convert test.file output.ps
~~~~

Sample output

~~~~
==19295==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7ffdd0d4bcc0 at pc 0x55d155b54159 bp 0x7ffdd0d4b1d0 sp 0x7ffdd0d4b1c0
WRITE of size 1 at 0x7ffdd0d4bcc0 thread T0
    #0 0x55d155b54158 in PopHexPixel coders/ps.c:1184
~~~~
