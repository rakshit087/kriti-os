# KritiOs
The project’s Goal to learn and implement concepts of Operating systems and create a toy UNIX type 32 bit OS from scratch which includes
The bootloader, drivers and some basic functionality.

## Tools Used

The Project utilizes NASM Assembly Compiler for assembly compilations and GCC Cross Compiler (elf-i386) to compile C code for 32 Bit machines. 
For virtualization and testing,  qemu was used. 
Linux’s make command was also utilized for hassle free compilations.  

The project was also tested on a spare laptop without any OS installed, which worked fine.

## Modules

### The Bootloader

A bootloader, also known as a boot program or bootstrap loader, is a special operating system software that loads into the working memory of a computer after start-up.
Our Bootloader is divided into three parts -
* Boot.asm - Greets the user and loads the loader.asm. We have kept the loader on a different memory location for better memory management.
* Loader.asm - It loads the kernel on the memory, loads the Global Descriptor Table, switches to 32 Bits and Jump to the Kernel.
* Routines - These are some common functions which are used throughout the bootloader, for example print in real mode and wait for user input.

### The Kernel

I have divided kernel into 4 parts.
* Drivers - It contains all the drivers including the video and keyboard drivers.
* Cpu - It contains functions related to CPU like handling interrupts.
* General - This file contains general functions which are required throughout the kernel, like memcpy, reverse etc
* Kernel.c - The main kernel file which is loaded when we boot our OS.

## Gallery

![image](https://user-images.githubusercontent.com/50898928/187917260-16547852-7657-4872-8194-59f07b985c7d.png)


## References

This project was made possible by the OSDevWiki: https://wiki.osdev.org & this repo: https://github.com/cfenollosa/os-tutorial
