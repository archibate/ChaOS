#pragma once

#include <inttypes.h>
#include <tol/iovec.h>
#include <tol/region.h>

typedef _region_type(ulong) l4Region_t;

typedef struct l4ShortMsg
{
	ulong raw0;
}
l4ShortMsg_t;

typedef struct l4MsgInfo
{
	l4ShortMsg_t mshrt;
	l4Region_t reg;
}
l4MsgInfo_t;

#define l4miSetShortMsg(mi, mshrt)		((mi)->mshrt = (mshrt))
#define l4miSetLongMsg(mi, base, len)	((void)((mi)->reg = (l4Region_t){beg: (ulong)(base), end: (base) + (len)}))
#define l4miSetLongMsgv(mi, base, len)	((void)((mi)->reg = (l4Region_t){beg: (iov)->base, end: (iov)->base + (iov)->len}))
#define l4miGetLongMsgv(mi)				((iovec_t){base: (void*)(mi)->reg.beg, len: (mi)->reg.end - (mi)->reg.beg})
