# Trying to fuzz PulseAudio

TODO:

**Needs a proper commandline binary**

Install AFL

~~~~bash
sudo apt install afl afl-clang afl-cov afl-doc
~~~~

Install dependencies

~~~~bash
sudo apt-get -qq -y install git-core autopoint autoconf automake intltool check libasound2-dev libasyncns-dev libatomic-ops-dev libavahi-client-dev libbluetooth-dev libsbc-dev libcap-dev libfftw3-dev libgconf2-dev libglib2.0-dev libgtk-3-dev libice-dev libjack-dev libjson-c-dev liblircclient-dev libltdl-dev liborc-0.4-dev libsamplerate0-dev libsndfile1-dev libspeexdsp-dev libssl-dev libtdb-dev libudev-dev libwebrtc-audio-processing-dev libwrap0-dev libx11-xcb-dev libxcb1-dev libxtst-dev
~~~~

Get the Code to be Fuzzed

~~~~bash
git clone git://anongit.freedesktop.org/pulseaudio/pulseaudio
~~~~

Build

~~~~bash
cd pulseaudio

export AFL_USE_ASAN=1
export CC=/usr/bin/afl-gcc
export CXX=/usr/bin/afl-g++

NOCONFIGURE=1 ./bootstrap.sh

./configure --localstatedir=/var && make && make check && make check-daemon && make install DESTDIR=`mktemp -d`
~~~~

Look at the test log

~~~~bash
cat src/test-suite.log
~~~~

Run the failing test

~~~~bash
export LD_LIBRARY_PATH=/home/patricia-gallardo/Code/pulseaudio/src/.libs/
./src/.libs/core-util-test
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
echo "-" > afl_corpus/test.txt
~~~~

Run AFL

~~~~bash
afl-fuzz -m none -i afl_corpus/ -o afl_output/ ./src/.libs/core-util-test @@
~~~~
