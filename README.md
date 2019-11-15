# insecure-fuzz

* [GhostScript](GHOST_SCRIPT.md): Works?
* [ImageMagick](IMAGE_MAGICK.md): Works?
* [MediaServer](MEDIA_SERVER.md): Needs work
* [OpenSSL HeartBleed](OPEN_SSL_HB.md): Works?
* [PulseAudio](PULSE_AUDIO.md): Needs work

Things to try:

Set AFL_INST_RATIO to 100%

~~~~bash
AFL_INST_RATIO=100
~~~~

This currently includes -D_FORTIFY_SOURCE=2 and -fstack-protector-all.

~~~~bash
AFL_HARDEN=1
~~~~

Use clang fast

~~~~bash
CC=/usr/bin/afl-clang-fast ./configure
CXX=/usr/bin/afl-clang-fast++ ./configure
~~~~

Minimize the corpus

~~~~bash
afl-cmin -i <input_folder> -o <output_folder> -- <binary> <options> @@
~~~~

Minimize the test
~~~~bash
afl-tmin -i <test_case> -o <output> -- <binary> <options> @@
~~~~

# Notes
Might need: root changes for AFL
(cat /usr/share/doc/afl-doc/docs/notes_for_asan.txt)

~~~~bash
sudo su -
echo core >/proc/sys/kernel/core_pattern
cd /sys/devices/system/cpu
echo performance | tee cpu*/cpufreq/scaling_governor
~~~~
