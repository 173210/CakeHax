#ifndef memchunkhax_h
#define memchunkhax_h

#include <stdint.h>
#include "appcompat.h"
#include "firmcompat.h"

__attribute__((noreturn))
void memchunk_arm11hax(const void *func, const void *ctx, uintptr_t linear,
                       const struct app_offsets *app, const struct firmware_offsets *fw);

#endif
