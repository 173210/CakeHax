#include <stdint.h>
#include "firmcompat.h"
#include "appcompat.h"
#include "memchunkhax.h"
#include "firmlaunchax.h"

static void arm11_kernel_code()
{
    __asm__ volatile ("clrex");

    // Reboot and load our arm9 payload in arm9 kernel mode
    firmlaunch_arm9hax();

    // We should never return here
    while (1) {};
}

void __attribute__((noreturn, section(".text.start"), used)) _start()
{
    uint32_t file_handle[8] = {0};
    void *fws;
    uint32_t n;

#ifdef ENTRY_SPIDER
    // Some offsets that differ per entry
    spider_set_app_offsets();
#endif

    app->fopen(&file_handle, APP_LAUNCHER_PATH, 1);

    if (*(uint32_t *)0x1FF80030 < 6) {
        file_handle[1] = 27136;
        n = FW_CTR_SIZE;
    } else {
        file_handle[1] = 27648;
        n = FW_KTR_SIZE;
    }

    fws = __builtin_alloca(n);
    app->fread(&file_handle, &n, fws, n);

    // Some offsets differ per firmware
    set_firmware_offsets(fws, n);

    file_handle[1] = 0x12000;
    app->fread(&file_handle, &n, (void *)(0x14000000 + APP_CFW_OFFSET),
               PAYLOAD_TABLE_SIZE + PAYLOAD_ARM9_SIZE);

    // Now, we gain arm11 kernel mode
    memchunk_arm11hax(arm11_kernel_code);
}
