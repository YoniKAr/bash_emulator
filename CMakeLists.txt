cmake_minimum_required(VERSION 3.15)
project(terminal_emulator)

add_executable(emulator emulator.cpp terminal.cpp bash_file_sys.cpp)

