#include "../firmcompat.h"

__attribute__((used)) const struct firmware_offsets ctr[] = {
    {
        // 2.34-0 4.1.0
        .ver = 0x02220000,

        .kernel_patch_address = 0xEFF83C97,
        .reboot_patch_address = 0xEFFF497C,
        .reboot_func_address = 0xFFF748C4,
        .jump_table_address = 0xEFFF4C80,
        .fcram_address = 0xF0000000,
        .func_patch_address = 0xEFFE4DD4,
        .func_patch_return = 0xFFF84DDC,
        .regs = 0xFFFCE000
    }, {
        // 2.35-6 5.0.0
        .ver = 0x02230600,

        .kernel_patch_address = 0xEFF8372F,
        .reboot_patch_address = 0xEFFF4978,
        .reboot_func_address = 0xFFF64B94,
        .jump_table_address = 0xEFFF4C80,
        .fcram_address = 0xF0000000,
        .func_patch_address = 0xEFFE55BC,
        .func_patch_return = 0xFFF765C4,
        .regs = 0xFFFCE000
    }, {
        // 2.36-0 5.1.0
        .ver = 0x02240000,

        .reboot_func_address = 0xFFF64B90,
        .func_patch_address = 0xEFFE55B8,
        .func_patch_return = 0xFFF765C0,
        .kernel_patch_address = 0xEFF8372B,
        .reboot_patch_address = 0xEFFF4978,
        .jump_table_address = 0xEFFF4C80,
        .fcram_address = 0xF0000000,
        .regs = 0xFFFCE000
    }, {
        // 2.37-0 6.0.0
        .ver = 0x02250000,

        .kernel_patch_address = 0xEFF8372B,
        .reboot_patch_address = 0xEFFF4978,
        .reboot_func_address = 0xFFF64A78,
        .func_patch_address = 0xEFFE5AE8,
        .func_patch_return = 0xFFF76AF0,
        .jump_table_address = 0xEFFF4C80,
        .fcram_address = 0xF0000000,
        .regs = 0xFFFCE000
    }, {
        // 2.38-0 6.1.0
        .ver = 0x02260000,

        .kernel_patch_address = 0xEFF8372B,
        .reboot_patch_address = 0xEFFF4978,
        .reboot_func_address = 0xFFF64A78,
        .func_patch_address = 0xEFFE5AE8,
        .func_patch_return = 0xFFF76AF0,
        .jump_table_address = 0xEFFF4C80,
        .fcram_address = 0xF0000000,
        .regs = 0xFFFCE000
    }, {
        // 2.39-4 7.0.0
        .ver = 0x02270400,

        .kernel_patch_address = 0xEFF8372F,
        .reboot_patch_address = 0xEFFF4978,
        .reboot_func_address = 0xFFF64AB0,
        .jump_table_address = 0xEFFF4C80,
        .fcram_address = 0xF0000000,
        .func_patch_address = 0xEFFE5B34,
        .func_patch_return = 0xFFF76B3C,
        .regs = 0xFFFCE000
    }, {
        // 2.40-0 7.2.0
        .ver = 0x02280000,

        .kernel_patch_address = 0xEFF8372B,
        .reboot_patch_address = 0xEFFF4978,
        .reboot_func_address = 0xFFF64AAC,
        .jump_table_address = 0xEFFF4C80,
        .fcram_address = 0xF0000000,
        .func_patch_address = 0xEFFE5B30,
        .func_patch_return = 0xFFF76B38,
        .regs = 0xFFFCE000
    }, {
        // 2.44-6 8.0.0
        .ver = 0x022C0600,

        .kernel_patch_address = 0xDFF83767,
        .reboot_patch_address = 0xDFFF4974,
        .reboot_func_address = 0xFFF54BAC,
        .jump_table_address = 0xDFFF4C80,
        .fcram_address = 0xE0000000,
        .func_patch_address = 0xDFFE4F28,
        .func_patch_return = 0xFFF66F30,
        .regs = 0xFFFBC000
    }, {
        // 2.26-0 9.0.0
        .ver = 0x022E0000,

        .kernel_patch_address = 0xDFF83837,
        .reboot_patch_address = 0xDFFF4974,
        .reboot_func_address = 0xFFF151C0,
        .jump_table_address = 0xDFFF4C80,
        .fcram_address = 0xE0000000,
        .func_patch_address = 0xDFFE59D0,
        .func_patch_return = 0xFFF279D8,
        .regs = 0xFFFC0000
    }
};
