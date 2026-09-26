cmake_minimum_required(VERSION 4.1)
project(nes_emulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(nes_emulator
        nes.c
        nes.h
        cpu.c
        cpu.h
)
