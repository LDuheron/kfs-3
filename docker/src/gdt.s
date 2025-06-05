.global writeGdtToRegisters

writeGdtToRegisters:
    movl 4(%esp), %eax    # Load the address of the GDT descriptor from the stack
    lgdt (%eax)           # Load the GDT

    movw $0x10, %ax       # Load the data segment selector into AX
    movw %ax, %ds         # Load DS with the data segment selector
    movw %ax, %es         # Load ES with the data segment selector
    movw %ax, %fs         # Load FS with the data segment selector
    movw %ax, %gs         # Load GS with the data segment selector
    movw %ax, %ss         # Load SS with the data segment selector

    ljmp $0x08, $.setCs   # Far jump to set the CS register
.setCs:
    ret
