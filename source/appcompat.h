#ifndef appcompat_h
#define appcompat_h

#include <stdint.h>
#include <wchar.h>

struct app_offsets
{
    int (*GSPGPU_FlushDataCache)(void *address, uint32_t length);
    void (*nn__gxlow__CTR__CmdReqQueueTx__TryEnqueue)(void *arg1, void *arg2);
    int (*fopen)(uint32_t (*handle)[], const wchar_t *path, int flags);
    int (*fread)(uint32_t (*handle)[], uint32_t *read, void *buffer, uint32_t size);

    uint32_t gpuHandle;
};

struct spider {
    uint32_t spec;
    struct app_offsets offsets;
};

extern const struct spider spiders[];

#endif
