# Trying to fuzz PulseAudio with LibFuzzer

Install Clang

~~~~bash
sudo apt install clang
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
export CC="clang -g -fsanitize=address,fuzzer-no-link"
NOCONFIGURE=1 ./bootstrap.sh
./configure --localstatedir=/var && make
unset CC
cd ..
~~~~

Get Fuzz Target

~~~~bash
curl -O https://raw.githubusercontent.com/patricia-gallardo/insecure-fuzz/master/fuzz_targets/pulse_audio/lib_fuzzer_pacat_simple.c
~~~~

Build Fuzz Target

~~~~bash
clang -g lib_fuzzer_pacat_simple.c -fsanitize=address,fuzzer pulseaudio/src/.libs/libpulse-simple.so pulseaudio/src/.libs/libpulse.so -ldl -o lib_fuzzer_pacat_simple
~~~~

Set up Initial Corpus and Output directories

~~~~bash
mkdir lf_corpus
cd lf_corpus
curl -O https://raw.githubusercontent.com/qt/qtmultimedia/dev/tests/auto/integration/qaudiodecoderbackend/testdata/test.wav
cd ..
~~~~

Run AFL

~~~~bash
export LD_LIBRARY_PATH=<path to the checkout>/pulseaudio/src/.libs/
./lib_fuzzer_pacat_simple lf_corpus
~~~~

Reproduce crash

~~~~bash
~~~~

Sample output

~~~~bash
~~~~
