cmake_minimum_required(VERSION 3.14)
project(Synthia)

set(CMAKE_CXX_STANDARD 17)

set(SYNTHIA_SOURCES
        synthia/Controllable.cc
        synthia/Delay.cc
        synthia/Envelope.cc
        synthia/Frames.cc
        synthia/Generator.cc
        synthia/Lowpass.cc
        synthia/PulseOscillator.cc
        #synthia/RetriggerGlitch.cpp
        synthia/SError.cc
        synthia/SineOscillator.cc
        synthia/SObject.cc
        #synthia/SoundFile.cc
        #synthia/SoundLoop.cc
        #synthia/SwitchableWavetableOscillator.cc
        synthia/SynthContext.cc
        synthia/SynthiaUtils.cc)
        #synthia/WavetableOscillator.cc)

add_library(synthia ${SYNTHIA_SOURCES})