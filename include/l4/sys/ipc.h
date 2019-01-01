#pragma once

#include <l4/sys/types.h>

#if 0
static int l4Call(chid_t chid,
		const l4MsgInfo_t *mSnd,
		l4MsgInfo_t *mRcv)
{
	int ret;
	asm volatile ("int $0x81"
			: "=a" (ret) : "a" (chid)
			, "c" (mSnd->reg.beg), "d" (mSnd->reg.end)
			);
	return ret;
}

static int l4CallNB(chid_t chid,
		const l4MsgInfo_t *mSnd,
		l4MsgInfo_t *mRcv)
{
	int ret;
	asm volatile ("int $0x82"
			: "=a" (ret) : "a" (chid)
			, "c" (mSnd->reg.beg), "d" (mSnd->reg.end)
			);
	return ret;
}
#endif

#if 0
static int l4Wait(chid_t chid,
		l4MsgInfo_t *mRcv)
{
	int ret;
	asm volatile ("int $0x83"
			: "=a" (ret), "=c" (mRcv->reg.beg), "=d" (mRcv->reg.end)
			: "a" (chid), "c" (mRcv->reg.beg), "d" (mRcv->reg.end)
			);
	return ret;
}
#endif

static int l4Wait(chid_t chid, l4FaultInfo_t *fi)
{
	int ret;
	asm volatile ("int $0x83"
			: "=a" (ret) : "a" (chid)
			, "c" (fi->offset), "d" (fi->errcd)
			);
	return ret;
}

static int l4Reply(chid_t chid, pid_t pid, ulong pgva)
{
	int ret;
	asm volatile ("int $0x84"
			: "=a" (ret) : "a" (chid), "b" (pid), "c" (pgva)
			);
	return ret;
}

static int l4SetPager(chid_t chid, const l4Region_t *reg)
{
	int ret;
	asm volatile ("int $0x80"
			: "=a" (ret) : "a" (chid)
			, "c" (reg->beg), "d" (reg->end)
			);
	return ret;
}
