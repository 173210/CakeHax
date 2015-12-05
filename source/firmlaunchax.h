#ifndef firmlaunchax_h
#define firmlaunchax_h

#include <stdint.h>
#include "firmcompat.h"

struct arm9hax_ctx {
    const struct firmware_offsets *fw;
    uintptr_t payload_offset;
};

void firmlaunch_arm9hax();

#endif
