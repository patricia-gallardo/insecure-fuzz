cmake_minimum_required(VERSION 3.10)
project(insecure-fuzz C CXX)
# https://github.com/conan-io/cmake-conan

if (NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(WARNING "Building for anything but 64 bit is currently untested")
endif ()

include(${CMAKE_SOURCE_DIR}/conan.cmake)

conan_check(VERSION 1.20.3 REQUIRED)
conan_add_remote(NAME bincrafters INDEX 1 URL https://api.bintray.com/conan/bincrafters/public-conan)
conan_cmake_run(CONANFILE conanfile.txt BASIC_SETUP CMAKE_TARGETS BUILD missing)

set(CMAKE_CPP_STANDARD 17)

# ------------------------
# PULSE AUDIO
# ------------------------

find_library(PULSE_LIB pulse)
find_library(PULSESIMPLE_LIB pulse-simple)

add_executable(pacat-simple fuzz_targets/pulse_audio/pacat-simple.c)
target_link_libraries(pacat-simple ${PULSE_LIB} ${PULSESIMPLE_LIB})

add_executable(parec-simple fuzz_targets/pulse_audio/parec-simple.c)
target_link_libraries(parec-simple ${PULSE_LIB} ${PULSESIMPLE_LIB})
