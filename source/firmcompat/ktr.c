#include "../firmcompat.h"

__attribute__((used)) const struct firmware_offsets ktr[] = {
    {
        // 9.0.0
        .ver = 0x022E0000,

        .kernel_patch_address = 0xDFF8382F,
        .reboot_patch_address = 0xDFFF4994,
        .reboot_func_address = 0xFFF158F8,
        .jump_table_address = 0xDFFF4C80,
        .fcram_address = 0xE0000000,
        .func_patch_address = 0xDFFE7A50,
        .func_patch_return = 0xFFF28A58,
        .regs = 0xFFFBC000
    }, {
        // N3DS 8.0.0
        .ver = 0x022C0600,

        .kernel_patch_address = 0xDFF8382F,
        .reboot_patch_address = 0xDFFF4994,
        .reboot_func_address = 0xFFF158F8,
        .jump_table_address = 0xDFFF4C80,
        .fcram_address = 0xE0000000,
        .func_patch_address = 0xDFFE7A50,
        .func_patch_return = 0xFFF28A58,
        .regs = 0xFFFBC000
    }
};
