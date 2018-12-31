#pragma once

#include <l4/sys/types.h>
#include <l4/sys/msginfo.h>

static int l4Call(chid_t chid,
		const l4MsgInfo_t *mSnd,
		l4MsgInfo_t *mRcv)
{
	int ret;
	asm volatile ("int $0x80"
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
	asm volatile ("int $0x81"
			: "=a" (ret) : "a" (chid)
			, "c" (mSnd->reg.beg), "d" (mSnd->reg.end)
			);
	return ret;
}

static int l4Wait(chid_t chid,
		l4MsgInfo_t *mRcv)
{
	int ret;
	asm volatile ("int $0x82"
			: "=a" (ret), "=c" (mRcv->reg.beg), "=d" (mRcv->reg.end)
			: "a" (chid), "c" (mRcv->reg.beg), "d" (mRcv->reg.end)
			);
	return ret;
}

static int l4Reply(chid_t chid, pid_t pid,
		const l4MsgInfo_t *mSnd)
{
	int ret;
	asm volatile ("int $0x83"
			: "=a" (ret) : "a" (chid), "b" (pid)
			, "c" (mSnd->reg.beg), "d" (mSnd->reg.end)
			);
	return ret;
}
