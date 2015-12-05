#include <stdint.h>
#include <wchar.h>
#include "firmcompat.h"
#include "appcompat.h"
#include "memchunkhax.h"
#include "firmlaunchax.h"
#include "launcher_path.h"

static void arm11_kernel_code(int res __attribute__((unused)),
                              int r1 __attribute__((unused)),
                              int r2 __attribute__((unused)),
                              int r3 __attribute__((unused)),
                              const struct arm9hax_ctx *ctx)
{
    __asm__ volatile ("clrex");

    // Reboot and load our arm9 payload in arm9 kernel mode
    firmlaunch_arm9hax(ctx);

    // We should never return here
    while (1) {};
}

__attribute__((noreturn, section(".text.start"), used))
void _start(const struct app_offsets *app, const wchar_t *path,
            uintptr_t linear, uintptr_t payload_offset)
{
    uint32_t file_handle[8] = {0};
    struct arm9hax_ctx ctx;
    const struct firmware_offsets *fw;
    void *fws;
    uint32_t n;

    app->fopen(&file_handle, path, 1);

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
    fw = get_firmware_offsets(fws, n);

    file_handle[1] = 0x12000;
    app->fread(&file_handle, &n, (void *)(0x14000000 + payload_offset),
               PAYLOAD_TABLE_SIZE + PAYLOAD_ARM9_SIZE);

    ctx.fw = fw;
    ctx.payload_offset = payload_offset;

    // Now, we gain arm11 kernel mode
    memchunk_arm11hax(arm11_kernel_code, &ctx, linear, app, fw);
}

__attribute__((noreturn, section(".text.spider"), used)) void spider()
{
    __attribute__((section(".rodata.spider")))
        static const wchar_t path[] = L"dmc:/" LAUNCHER_PATH;
    const struct spider *p;

    // Some offsets that differ per entry
    for (p = spiders; p->spec != *(uint32_t *)0x0010000C; p++);
    _start(&p->offsets, path, 0x18400000, 0x4410000);
}
