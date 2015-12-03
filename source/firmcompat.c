#include "firmcompat.h"

#include <stddef.h>
#include <stdint.h>

const struct firmware_offsets *fw;

int set_firmware_offsets(const struct firmware_offsets *p, size_t n)
{
    while (n > 0) {
        if (p->ver == *(uint32_t *)0x1FF80000) {
            fw = p;
            return 0;
        }

        n -= sizeof(struct firmware_offsets);
        p++;
    }

    return 1;
}
