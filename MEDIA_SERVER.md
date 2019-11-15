# Trying to fuzz MediaServer

Notes: Needs C++17 - will need to build AFL

Install AFL

~~~~bash
sudo apt install afl afl-clang afl-cov afl-doc
~~~~

Install dependencies

~~~~bash
sudo apt install libmagick++-dev
~~~~

Get the Code to be Fuzzed

~~~~bash
https://github.com/medooze/media-server.git
~~~~

Build

~~~~bash
cd media-server/
git submodule update --init --recursive

export AFL_USE_ASAN=1
export CC=/usr/bin/afl-clang-fast
export CXX=/usr/bin/afl-clang-fast++
export AFL_INST_RATIO=100

make fuzz
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
~~~~

Run AFL

~~~~bash
afl-fuzz -m none -i afl_corpus/ -o afl_output/ 
~~~~
