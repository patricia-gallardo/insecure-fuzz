cmake_minimum_required(VERSION 3.10)
project(insecure-fuzz C CXX)
# https://github.com/conan-io/cmake-conan

message(STATUS "Insecure-Fuzz: This file is not intended to be the real way to build this project")
message(STATUS "Insecure-Fuzz: Follow the individual markdown instructions")

message(STATUS "Insecure-Fuzz: Requires Clang for libFuzzer")

if (NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(WARNING "Insecure-Fuzz: Building for anything but 64 bit is currently untested")
endif ()

include(${CMAKE_SOURCE_DIR}/conan.cmake)

conan_check(VERSION 1.20.3 REQUIRED)
conan_add_remote(NAME bincrafters INDEX 1 URL https://api.bintray.com/conan/bincrafters/public-conan)
conan_cmake_run(CONANFILE conanfile.txt BASIC_SETUP CMAKE_TARGETS BUILD missing)

set(CMAKE_CPP_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------
# OPEN SSL
# ------------------------

add_executable(afl_handshake_fuzzer fuzz_targets/open_ssl_heartbleed/afl_handshake_fuzzer.cc)
target_link_libraries(afl_handshake_fuzzer CONAN_PKG::OpenSSL "stdc++fs")

add_executable(lib_fuzzer_handshake_fuzzer fuzz_targets/open_ssl_heartbleed/lib_fuzzer_handshake_fuzzer.cc)
target_link_libraries(lib_fuzzer_handshake_fuzzer CONAN_PKG::OpenSSL "stdc++fs")
set_target_properties(lib_fuzzer_handshake_fuzzer PROPERTIES
        LINK_FLAGS -fsanitize=address,fuzzer
        COMPILE_FLAGS -fsanitize=address,fuzzer)

# ------------------------
# PULSE AUDIO
# ------------------------

find_library(PULSE_LIB pulse)
find_library(PULSESIMPLE_LIB pulse-simple)

add_executable(afl_pacat_simple fuzz_targets/pulse_audio/afl_pacat_simple.c)
target_link_libraries(afl_pacat_simple ${PULSE_LIB} ${PULSESIMPLE_LIB})

add_executable(parec-simple fuzz_targets/pulse_audio/afl_parec_simple.c)
target_link_libraries(parec-simple ${PULSE_LIB} ${PULSESIMPLE_LIB})
