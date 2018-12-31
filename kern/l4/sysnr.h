#pragma once

typedef enum sysnr
{
	L4SYS_CALL = 0,
	L4SYS_CALLNB,
	L4SYS_WAIT,
	L4SYS_REPLY,
	L4SYS_REPLY_WAIT,
	L4_SYSNRS,
}
sysnr_t;
