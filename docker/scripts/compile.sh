#!/bin/bash
cd /home/mount/src
i386-elf-gcc -c gdt.c -o gdt.o -ffreestanding -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs
i386-elf-gcc -c kernel.c -o kernel.o -I ../inc/ -ffreestanding -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs
i386-elf-gcc -c stackPrinter.c -o stackPrinter.o -I ../inc/ -ffreestanding -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs
i386-elf-as boot.s -o boot.o
i386-elf-as gdt.s -o gdts.o
i386-elf-gcc -T linker.ld -o kfs.bin -ffreestanding -O2 -nostdlib boot.o kernel.o gdt.o gdts.o stackPrinter.o
