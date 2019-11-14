# Trying to fuzz ImageMagick

Install AFL

~~~~bash
sudo apt install afl afl-clang afl-cov afl-doc
~~~~

Install dependencies

~~~~bash

~~~~

Clone the repo

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

Set up test cases

~~~~bash
mkdir in
mkdir out
cp images/*.jpg in/
cp www/Magick++/*.jpg in/
cp PerlMagick/t/jpeg/*.jpg in/
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
afl-fuzz -m none -i in/ -o out/ ./utilities/magick convert @@ output.png
~~~~
