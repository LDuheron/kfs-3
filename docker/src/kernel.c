#include "../inc/stdint.h"
#include "../inc/stddef.h"
#include "../inc/gdt.h"
#include "stackPrinter.h"

#define VGA_HEIGHT 30
#define VGA_WIDTH 80

// #if defined(__linux__)
// #error "You are not using a cross-compiler, you will most certainly run into trouble"
// #endif

// #if !defined(__i386__)
// #error "KernAL is meant to be run on i386 machines"
// #endif

enum vga_color {
	VGA_BLACK = 0,
	VGA_BLUE = 1,
	VGA_GREEN = 2,
	VGA_CYAN = 3,
	VGA_RED = 4,
	VGA_MAGENTA = 5,
	VGA_BROWN = 6,
	VGA_LIGHT_GREY = 7,
	VGA_DARK_GREY = 8,
	VGA_LIGHT_BLUE = 9,
	VGA_LIGHT_GREEN = 10,
	VGA_LIGHT_CYAN = 11,
	VGA_LIGHT_RED = 12,
	VGA_LIGHT_MAGENTA = 13,
	VGA_LIGHT_BROWN = 14,
	VGA_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char c, uint8_t color) {
    return (uint16_t) c | (uint16_t) color << 8;
}

size_t terminal_row = 0;
size_t terminal_column = 0;
uint8_t terminal_color;
uint16_t* terminalBuffer = (uint16_t*) 0xB8000;

void terminal_initialize(void) {
    terminal_color = vga_entry_color(VGA_WHITE, VGA_BLACK);
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminalBuffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminalBuffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) 
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

void terminal_writestring(const char* data) {
    size_t i = 0;
    while (data[i]) {
        terminal_putchar(data[i++]);
    }
}

extern void * stack_top;
void    kernel_main(void)
{
	char i[] = "42";

    terminal_initialize();
    initGdt();
    writeStackToVga((void *)&i, 1000, terminalBuffer);
    //writeStackToVga((void *)stack_top, 1000, terminalBuffer);
}
