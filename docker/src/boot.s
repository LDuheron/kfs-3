/* Definition of Multiboot header constant */
.set ALIGN,    1<<0                 /* Align modules on page boundaries */
.set MEMINFO,  1<<1                 /* Provide memory map */
.set FLAGS,    ALIGN | MEMINFO      /* Multiboot flags */
.set MAGIC,    0x1BADB002           /* Magic number for bootloader identification*/
.set CHECKSUM, -(MAGIC + FLAGS)     /* Checksum to validate header */

/* Multiboot header marking the program as a kernel */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* Initialize a 16KiB stack with 16-byte alignment */
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
.global stack_top
stack_top:

/* Kernel entrypoint specified by linker script */
.section .text
.global _start
.type _start, @function
_start:
    /* Set up stack pointer for the kernel's stack */
	mov $stack_top, %esp

	/* Load the GDTR */
/*	call initGdt */

    /* Call kernel main function from kernel.c */
	call kernel_main

    /* Halt the system if kernel_main returns */
	cli
1:	hlt
	jmp 1b

/* Defining the Global Descriptor Table Register */
gdtr:
	/*Size of the GDT ((7 entries * 8 bytes) - 1)*/
	.word 0x37
	/*Base address of the GDT*/
	.quad 0x00000800

/* Defines the size of _start by calculating the
difference between its curent location and its 
starting address (useful for debugging and linking purposes) */ 
.size _start, . - _start
