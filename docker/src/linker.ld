OUTPUT_FORMAT(elf32-i386)

ENTRY(_start)

SECTIONS
{
	. = 1M;

	.text BLOCK(4k) : ALIGN(4)
	{
		*(.multiboot)
		*(.text)
	}
	.data BLOCK(4k) : ALIGN(4)
	{
		*(.data)
	}
	.bss BLOCK(4k) : ALIGN(4)
	{
		*(.bss)
	}
}
