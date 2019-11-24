# Trying to fuzz PulseAudio with AFL

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
export CC=/usr/bin/afl-clang-fast
export CXX=/usr/bin/afl-clang-fast++
export AFL_INST_RATIO=100

NOCONFIGURE=1 ./bootstrap.sh

./configure --localstatedir=/var && make && make check && make check-daemon && make install DESTDIR=`mktemp -d`
~~~~

Get Fuzz Target

~~~~bash
curl -O https://raw.githubusercontent.com/patricia-gallardo/insecure-fuzz/master/fuzz_targets/fuzz_targets/pulse_audio/afl_pacat_simple.c
~~~~

Build Fuzz Target

~~~~bash
$CC -g afl_pacat_simple.c pulseaudio/src/.libs/libpulse-simple.so pulseaudio/src/.libs/libpulse.so -o afl_pacat_simple
~~~~

Set up Initial Corpus and Output directories

~~~~bash
mkdir afl_corpus afl_output
cd afl_corpus
curl -O https://raw.githubusercontent.com/qt/qtmultimedia/dev/tests/auto/integration/qaudiodecoderbackend/testdata/test.wav
cd ..
~~~~

Run AFL

~~~~bash
export LD_LIBRARY_PATH=<path to the checkout>/pulseaudio/src/.libs/
afl-fuzz -m none -i afl_corpus/ -o afl_output/ ./afl_pacat_simple @@
~~~~

Reproduce crash

~~~~bash
./afl_pacat_simple afl_output/crashes/<file>
~~~~

Sample output

~~~~bash
~~~~
