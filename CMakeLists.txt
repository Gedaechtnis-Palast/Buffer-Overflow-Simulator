cmake_minimum_required(VERSION 3.22)
project(Buffer-Overflow-Simulator C)

set(CMAKE_C_STANDARD 23)

add_executable(${PROJECT_NAME} main.c textinput.c loopEntryAttack.c fileinput.c memoryMapping.c returnAddressAttack.c)
