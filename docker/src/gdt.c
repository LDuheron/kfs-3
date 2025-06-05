#include "../inc/stdint.h"
#include "../inc/stddef.h"
#include "../inc/gdt.h"


struct gdt_segment_descriptor_struct gdt_entries[7];
struct gdt_ptr_struct gdt_ptr;

static void setGdtEntries(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt_entries[index].limit = LOWER_16_BITS(limit);

    gdt_entries[index].baseLow = LOWER_16_BITS(base);
    gdt_entries[index].baseMid = BITS_16_TO_24(base);

    gdt_entries[index].accessByte = access;

    gdt_entries[index].flags = BITS_16_TO_20(limit);
    gdt_entries[index].flags |= ISOLATE_BITS_4_TO_8(granularity);

    gdt_entries[index].baseHigh = BITS_24_TO_32(base);
}

void initGdt() {
    gdt_ptr.limit = (sizeof(struct gdt_segment_descriptor_struct) * 7) - 1;
    gdt_ptr.base = (unsigned int) &gdt_entries;

    setGdtEntries(0, 0, 0, 0, 0);
    setGdtEntries(1, 0, LIMIT, KERNEL_MODE | CODE_MODE, FLAG); // Kernel code
    setGdtEntries(2, 0, LIMIT, KERNEL_MODE | DATA_MODE, FLAG); // Kernel data
    setGdtEntries(3, 0, LIMIT, KERNEL_MODE | DATA_MODE, FLAG); // Kernel stack

    setGdtEntries(4, 0, LIMIT, USER_MODE | CODE_MODE, FLAG); // User code
    setGdtEntries(5, 0, LIMIT, USER_MODE | DATA_MODE, FLAG); // User data
    setGdtEntries(6, 0, LIMIT, USER_MODE | DATA_MODE, FLAG); // User stack

    writeGdtToRegisters(&gdt_ptr);
}
