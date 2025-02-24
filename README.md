# Buffer Overflow Simulator

<!-- TOC -->
* [Buffer Overflow Simulator](#buffer-overflow-simulator)
  * [Motivation behind this Project](#motivation-behind-this-project)
  * [Setup Guide](#setup-guide)
    * [Windows Setup](#windows-setup)
    * [Linux Setup](#linux-setup)
  * [User Guide](#user-guide)
<!-- TOC -->

## Motivation behind this Project

Buffer Overflow attacks are widely known in the world of IT Security.  
Those attacks are most prominent in low level languages without automatic memory handling.  
Since C is one of those languages with manual memory handling, the buffer overflow topic is a perfect fit for a project written in C.

This project focuses on simulating a buffer overflow without relying on dangerous memory manipulation.  
It showcases how a hacker could attack unsafe functions, exploiting insecure memory handling to cause a lot of damage.  
Making this project executable, on any machine without requiring to disable all the kernel level security mechanisms like,  
DEP, ASLR and stack canaries, was one of the biggest challenges of this project.

You can find more information about the technical details in the [Developer documentation](DeveloperDocumentation.md).

Before starting with the project make sure to read the following:
 - [Setup Guide](#setup-guide)
 - [User Guide](#user-guide)

## Setup Guide

This project provides a CMakeLists.txt which requires the following:
 - CMake Version 3.22+ (For automatic Makefile generation)
 - Make(Linux)/mingw32-make(Windows)

### Windows Setup

For Windows using VSCode has been the most reliable option as there is a full guide on how to get Msys2 and MinGW:
- [Download Guide](https://code.visualstudio.com/docs/cpp/config-mingw) (If you don't use VSCode just skip the plugin install and follow the rest of the [setup video](https://code.visualstudio.com/docs/cpp/config-mingw#_installing-the-mingww64-toolchain))

For CMake, you just need a precompiled version 3.22+:
 - [Link to precompiled CMake](https://cmake.org/download/#latest)  
   Install it, unpack it and add the binary to your PATH

After that you should be able to build this project:
1. Clone the project: ``git clone <clone-url>``
2. Open CMD and switch to the project folder: ``cd path\to\project\folder``
3. Create a build folder: ``mkdir build``
4. Switch into the build folder: ``cd build``
5. Let CMake build the Makefiles for you: ``cmake .. -G "MinGW Makefiles"``
6. Run ``mingw32-make`` to compile the project files
7. Run ``.\Buffer-Overflow-Simulator.exe -h`` to see all the flags available

### Linux Setup
To install CMake you can follow this [CMake installation guide](https://askubuntu.com/a/865294) 

To install make follow this [Make installation guide](https://askubuntu.com/a/272020)

After that you should be able to build this project:
1. Clone the project: ``git clone <clone-url>``
2. Open CMD and switch to the project folder: ``cd path/to/project/folder``
3. Create a build folder: ``mkdir build``
4. Switch into the build folder: ``cd build``
5. Let CMake build the Makefiles for you: ``cmake ..``
6. Run ``make`` to compile the project files
7. Run ``.\Buffer-Overflow-Simulator -h`` to see all the flags available

## User Guide

Please read the [Setup guide](#setup-guide) first before continuing further.

After building the project you can run the ``.\Buffer-Overflow-Simulator -h`` or ``.\Buffer-Overflow-Simulator.exe -h`` command to get more info about the available options.

There are two game like attacks you can start, a loop entry attack and a return address overwrite attack.

### Loop Entry Attack

