# Trying to fuzz MediaServer

Install AFL

~~~~bash
sudo apt install afl afl-clang afl-cov afl-doc
~~~~

Install dependencies

~~~~bash
sudo apt install libmagick++-dev
~~~~

Clone the repo

~~~~bash
https://github.com/medooze/media-server.git
~~~~

Build

~~~~bash
cd media-server/

export AFL_USE_ASAN=1
export CC=/usr/bin/afl-clang-fast
export CXX=/usr/bin/afl-clang-fast++
export AFL_INST_RATIO=100

make fuzz
~~~~

Set up test cases

~~~~bash
mkdir afl_corpus
mkdir afl_output
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
afl-fuzz -m none -i afl_corpus/ -o afl_output/ 
~~~~
