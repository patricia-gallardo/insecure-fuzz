# Trying to fuzz ImageMagick

Install AFL

~~~~bash
sudo apt install afl afl-clang afl-cov afl-doc
~~~~

Install dependencies

~~~~bash

~~~~

Get the Code to be Fuzzed

~~~~bash
git clone https://github.com/ImageMagick/ImageMagick.git
~~~~

Build

~~~~bash
cd ImageMagick

export AFL_USE_ASAN=1
export CC=/usr/bin/afl-gcc
export CXX=/usr/bin/afl-g++

./configure --disable-shared && make
~~~~

Get Fuzz Target

~~~~bash
~~~~

Build Fuzz Target

~~~~bash
~~~~

Set up Initial Corpus and Output directories

~~~~bash
mkdir afl_corpus
mkdir afl_output
cp images/*.jpg afl_corpus/
cp www/Magick++/*.jpg afl_corpus/
cp PerlMagick/t/jpeg/*.jpg afl_corpus/
~~~~

Run AFL

~~~~bash
afl-fuzz -m none -i afl_corpus/ -o afl_output/ ./utilities/magick convert @@ output.png
~~~~
