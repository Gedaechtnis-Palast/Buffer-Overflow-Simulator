# Buffer Overflow Simulator

<!-- TOC -->
* [Buffer Overflow Simulator](#buffer-overflow-simulator)
  * [Motivation behind this Project](#motivation-behind-this-project)
  * [Setup Guide](#setup-guide)
    * [Windows Setup](#windows-setup)
    * [Linux Setup](#linux-setup)
  * [User Guide](#user-guide)
    * [Memory visualization](#memory-visualization)
    * [Loop Entry Attack](#loop-entry-attack)
    * [Return Address Attack](#return-address-attack)
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
 - Make (Linux) / mingw32-make (Windows)

### Windows Setup

For Windows using VSCode has been the most reliable option as there is a full guide on how to get Msys2 and MinGW:
- [Download Guide](https://code.visualstudio.com/docs/cpp/config-mingw) (If you don't use VSCode just skip the plugin install and follow the rest of the [setup video](https://code.visualstudio.com/docs/cpp/config-mingw#_installing-the-mingww64-toolchain))

For CMake, you just need a precompiled version 3.22+:
 - [Link to precompiled CMake](https://cmake.org/download/#latest)  
   Install it, unpack it and add the binary to your PATH

After that you should be able to build this project:
1. Clone the project: `git clone <clone-url>`  
(replace `<clone-url>` with the url from the `<>Code` button)
2. Open CMD and switch to the project folder: `cd path\to\project\folder`  
(replace `path\to\project\folder` with the actual path to the cloned project on your machine)
3. Create a build folder: `mkdir build`
4. Switch into the build folder: `cd build`
5. Let CMake build the Makefiles for you: `cmake .. -G "MinGW Makefiles"`  
(the generator "MinGW Makefiles" works fine but you can use other ones if you like)
6. Run `mingw32-make` to compile the project files
7. Run `.\Buffer-Overflow-Simulator.exe -h` to see all the flags available

### Linux Setup
To install CMake you can follow this [CMake installation guide](https://askubuntu.com/a/865294) 

To install make follow this [Make installation guide](https://askubuntu.com/a/272020)

After that you should be able to build this project:
1. Clone the project: `git clone <clone-url>`
2. Open your Terminal and switch to the project folder: `cd path/to/project/folder`
3. Create a build folder: `mkdir build`
4. Switch into the build folder: `cd build`
5. Let CMake build the Makefiles for you: `cmake ..`
6. Run `make` to compile the project files
7. Run `.\Buffer-Overflow-Simulator -h` to see all the flags available

## User Guide

Please read the [Setup guide](#setup-guide) first before continuing further.

After building the project you can run the `.\Buffer-Overflow-Simulator -h` or `.\Buffer-Overflow-Simulator.exe -h` command to get more info about the available options.

There are two game like attacks you can start, a loop entry attack and a return address overwrite attack.

### Memory visualization

Before going into the attack simulations the visualization needs to be explained.  
There are three main areas in the memory, the stack, heap and static memory.  
Each of them are separately displayed and show what memory the program is using (it does not show everything but the necessary parts).  
There are four indicators to look out for:
 - White bars (pipes) - indicating memory addresses not used by the program
 - Green bars (pipes) - indicating memory addresses rightfully used by the program
 - Red bars (pipes) - indicating memory addresses maliciously used by the program indicating a buffer overflow
 - Yellow truncated message - indicating how many unused addresses have been truncated/omitted due to the space limitations of the terminal

Unused memory addresses does not mean the memory addresses are not used by any program, it means this program does not use those addresses by itself.

### Loop Entry Attack

Make sure to have a big terminal, since the memory visualization output pushes the feedback output up, sometimes out of sight for the user.

The loop entry attack allows you to input some text, which will be safely evaluated and processed to check if your buffer overflow has successfully caused the loop to execute.

Just run `.\Buffer-Overflow-Simulator --loop-entry-attack` and start typing.  
The program will infinitely ask for your input, giving you an option to generate a buffer overflow.  
The program will keep you there until you successfully entered the loop or you terminate the progam with `Ctrl + C`.

You can also provide a file path by using `-p <path/to/text/file>`.  
Another option would be to use the `--use-file-input` flag allowing you to enter the filepath on runtime inside the terminal.  
Whenever you use a file as input to attempt a buffer overflow attack, it will immediately stop the execution, either the buffer enters the loop or not.  
Causing the overflow to enter the loop is close to what a hacker has to do, though in a real attack it is much harder to be successful.

### Return Address Attack

Make sure to have a big terminal, since the memory visualization output pushes the feedback output up, sometimes out of sight for the user.

The return address attack works like the Loop entry attack though it will be more verbose about your progress.  
If you don't see any output in the Terminal (above the output which visualizes the memory used) you did not yet cause buffer overflow, just keep playing around.

Once you succeed to cause a buffer overflow, the program gets more verbose, printing some gibberish and an indicator like: `_ _ _ _ _ _ _ _ _ _`  
This output tells you if you are already overwriting the return address and if the new address you provide matches a random address chosen by the program.  (the address is a decimal number like **`1234567890`**)  
You will know when you are overwriting the address when an `x` is displayed instead of the `_`.  
Your goal is now to guess the address combination, each `x` will turn into a number when you guessed the correct one for this spot (make sure you don't remove it accidentally).  
Keep in mind a real hacker does not have such a helpful output,
they need to experiment around blindly increasing the risk of crashing the program and drawing attention to the vulnerability.  
Try to be as efficient as possible, it is easy enough to succeed but hard enough to show how much effort it is to perform such an attack.

You can use the `--use-dep` flag for a different ending of this little game.