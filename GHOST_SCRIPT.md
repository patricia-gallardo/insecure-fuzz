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
export CC=/usr/bin/afl-gcc
export CXX=/usr/bin/afl-g++

./autogen.sh
./configure && make
#make so
~~~~

Set up test cases

~~~~bash
mkdir afl_in
mkdir afl_out
cd afl_in
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
afl-fuzz -m none -i afl_in/ -o afl_out/ ./bin/gs -sDEVICE=pdfwrite -o output.pdf @@
~~~~
