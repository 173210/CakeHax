#include <stdint.h>
#include "appcompat.h"

const struct app_offsets *app;

#ifdef ENTRY_SPIDER
struct spider {
    uint32_t spec;
    struct app_offsets offsets;
};

static const struct spider spiders[] = {
    {
        // 4.x
        .spec = 0xEB0676B5,
	.offsets = {
            .GSPGPU_FlushDataCache = (void *)0x00344B84,
            .nn__gxlow__CTR__CmdReqQueueTx__TryEnqueue = (void *)0x002CF3EC,
            .fopen = (void *)0x0025B0A4,
            .fread = (void *)0x002FC8E4,

            .gpuHandle = (0x003F54E8 + 0x58)
	}
    }, {
        // 5.x
        .spec = 0xEB050B2A,
        .offsets = {
            .GSPGPU_FlushDataCache = (void *)0x001914FC,
            .nn__gxlow__CTR__CmdReqQueueTx__TryEnqueue = (void *)0x0012BF4C,
            .fopen = (void *)0x0022FE44,
            .fread = (void *)0x001686C0,

            .gpuHandle = (0x003D7C40 + 0x58)
        }
    }, {
        // 9.x
        .spec = 0xEB050B28,
        .offsets = {
            .GSPGPU_FlushDataCache = (void *)0x00191504,
            .nn__gxlow__CTR__CmdReqQueueTx__TryEnqueue = (void *)0x0012BF04,
            .fopen = (void *)0x0022FE08,
            .fread = (void *)0x001686DC,

            .gpuHandle = (0x003D7C40 + 0x58)
        }
    }, {
        // 4.2 CN
        .spec = 0xEB050466,
        .offsets = {
            .GSPGPU_FlushDataCache = (void *)0x00190118,
            .nn__gxlow__CTR__CmdReqQueueTx__TryEnqueue = (void *)0x0012BA40,
            .fopen = (void *)0x0022E334,
            .fread = (void *)0x001674BC,

            .gpuHandle = (0x003D6C40 + 0x58)
        }
    }, {
        // 4.5 CN
        .spec = 0xEB05043C,
        .offsets = {
            .GSPGPU_FlushDataCache = (void *)0x0018FC0C,
            .nn__gxlow__CTR__CmdReqQueueTx__TryEnqueue = (void *)0x0012BA54,
            .fopen = (void *)0x0022E2B0,
            .fread = (void *)0x00166FC8,

            .gpuHandle = (0x003D6C40 + 0x58)
        }
    }, {
        // 5.x CN
        .spec = 0xEB050657,
        .offsets = {
            .GSPGPU_FlushDataCache = (void *)0x001902A8,
            .nn__gxlow__CTR__CmdReqQueueTx__TryEnqueue = (void *)0x0012BA6C,
            .fopen = (void *)0x0022EA5C,
            .fread = (void *)0x0016751C,

            .gpuHandle = (0x003D7C40 + 0x58)
        }
    }, {
        // 9.x CN
        .spec = 0xEB050656,
        .offsets = {
            .GSPGPU_FlushDataCache = (void *)0x001902B8,
            .nn__gxlow__CTR__CmdReqQueueTx__TryEnqueue = (void *)0x0012BA24,
            .fopen = (void *)0x0022EA24,
            .fread = (void *)0x00167540,

            .gpuHandle = (0x003D7C40 + 0x58)
        }
    }, {
        // 4.x KR
        .spec = 0xEB050838,
        .offsets = {
            .GSPGPU_FlushDataCache = (void *)0x00190D30,
            .nn__gxlow__CTR__CmdReqQueueTx__TryEnqueue = (void *)0x0012BA14,
            .fopen = (void *)0x0022F284,
            .fread = (void *)0x001680F8,

            .gpuHandle = (0x003D7C40 + 0x58)
        }
    }, {
        // 5.x KR
        .spec = 0xEB050A4B,
        .offsets = {
            .GSPGPU_FlushDataCache = (void *)0x0019154C,
            .nn__gxlow__CTR__CmdReqQueueTx__TryEnqueue = (void *)0x0012BA40,
            .fopen = (void *)0x0022FAC8,
            .fread = (void *)0x001686FC,

            .gpuHandle = (0x003D7C40 + 0x58)
        }
    }, {
        // 9.x KR
        .spec = 0xEB050A49,
        .offsets = {
            .GSPGPU_FlushDataCache = (void *)0x00191554,
            .nn__gxlow__CTR__CmdReqQueueTx__TryEnqueue = (void *)0x0012B9F8,
            .fopen = (void *)0x0022FA8C,
            .fread = (void *)0x00168718,

            .gpuHandle = (0x003D7C40 + 0x58)
        }
    }, {
        // 4.x TW
        .spec = 0xEB05084D,
        .offsets = {
            .GSPGPU_FlushDataCache = (void *)0x00190D34,
            .nn__gxlow__CTR__CmdReqQueueTx__TryEnqueue = (void *)0x0012BA40,
            .fopen = (void *)0x0022F2D8,
            .fread = (void *)0x001680FC,

            .gpuHandle = (0x003D7C40 + 0x58)
        }
    }, {
        // 5.x TW
        .spec = 0xEB050A70,
        .offsets = {
            .GSPGPU_FlushDataCache = (void *)0x00191594,
            .nn__gxlow__CTR__CmdReqQueueTx__TryEnqueue = (void *)0x0012BA6C,
            .fopen = (void *)0x0022FB5C,
            .fread = (void *)0x00168744,

            .gpuHandle = (0x003D7C40 + 0x58)
        }
    }, {
        // 9.x TW
        .spec = 0xEB050A6E,
        .offsets = {
            .GSPGPU_FlushDataCache = (void *)0x0019159C,
            .nn__gxlow__CTR__CmdReqQueueTx__TryEnqueue = (void *)0x0012BA24,
            .fopen = (void *)0x0022FB20,
            .fread = (void *)0x00168760,

            .gpuHandle = (0x003D7C40 + 0x58)
        }
    }
};

int spider_set_app_offsets()
{
    const struct spider *cur, *btm;

    cur = spiders;
    for (btm = cur + sizeof(spiders) / sizeof(struct app_offsets); cur != btm; cur++)
        if (cur->spec == *(uint32_t *)0x0010000C) {
            app = &cur->offsets;
            return 0;
        }

    return 1;
}
#endif
