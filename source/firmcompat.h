#ifndef firmcompat_h
#define firmcompat_h

#include <stddef.h>
#include <stdint.h>
#include "appcompat.h"

struct firmware_offsets {
    uint32_t ver;

    uint32_t kernel_patch_address;
    uint32_t reboot_patch_address;
    uint32_t reboot_func_address;
    uint32_t jump_table_address;
    uint32_t fcram_address;
    uint32_t func_patch_address;
    uint32_t func_patch_return;
    uint32_t regs;
};

const struct firmware_offsets *get_firmware_offsets(
    const struct firmware_offsets *p, size_t n);

#endif
