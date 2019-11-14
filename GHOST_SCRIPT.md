# Trying to fuzz GhostScript

[https://www.ghostscript.com/doc/current/Make.htm]

Install AFL

~~~~bash
sudo apt install afl afl-clang afl-cov afl-doc
~~~~

Install dependencies

~~~~bash

~~~~

Clone the repo

~~~~bash
git clone git://git.ghostscript.com/ghostpdl.git
~~~~

Build

~~~~bash
cd ghostpdl

export AFL_USE_ASAN=1
export CC=/usr/bin/afl-clang-fast ./configure
export CXX=/usr/bin/afl-clang-fast++ ./configure
export AFL_INST_RATIO=100

./autogen.sh
./configure && make
#make so
~~~~

Set up test cases

~~~~bash
mkdir afl_corpus afl_output
cd afl_corpus
wget https://people.sc.fsu.edu/~jburkardt/data/ps/bell_206.ps
~~~~

Might need: root changes for AFL

~~~~bash
sudo su -
echo core >/proc/sys/kernel/core_pattern
cd /sys/devices/system/cpu
echo performance | tee cpu*/cpufreq/scaling_governor
~~~~

Run AFL
(cat /usr/share/doc/afl-doc/docs/notes_for_asan.txt)

~~~~bash
afl-fuzz -m none -i afl_corpus/ -o afl_output/ ./bin/gs -sDEVICE=pdfwrite -o output.pdf @@
~~~~
