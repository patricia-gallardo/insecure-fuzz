# Trying to fuzz GhostScript

[https://www.ghostscript.com/doc/current/Make.htm]

Install AFL

~~~~bash
sudo apt install afl afl-clang afl-cov afl-doc
~~~~

Install dependencies

~~~~bash

~~~~

Get the Code to be Fuzzed

~~~~bash
git clone git://git.ghostscript.com/ghostpdl.git
~~~~

Build

~~~~bash
cd ghostpdl

export AFL_USE_ASAN=1
export CC=/usr/bin/afl-clang-fast
export CXX=/usr/bin/afl-clang-fast++
export AFL_INST_RATIO=100

./autogen.sh
./configure && make
#make so
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
cd afl_corpus
wget https://people.sc.fsu.edu/~jburkardt/data/ps/bell_206.ps
~~~~

Run AFL

~~~~bash
afl-fuzz -m none -i afl_corpus/ -o afl_output/ ./bin/gs -sDEVICE=pdfwrite -o output.pdf @@
~~~~
