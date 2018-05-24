# README

This repository contains code demonstration the directory scanning 
classes. The purpose is to port this code into the `mldb` client to 
provide improved 'ls' functionality.

## Build System

The project uses CLion as the `IDE` and `CMake` as the build system.

## Tested on

* Linux g++
* Windows (Cygwin) g++
* MinGW32 g++

## Notes concerning ANSI color

This code outputs ANSI color codes to the console. Windows consoles
have not 'traditionally' supported ANSI codes but newer console applications
such as MSYS2 and ConEMU provide support.

This code has been tested with:

* Cygwin Bash MinTTY console
* MSYS2 console
* ConEMU console
