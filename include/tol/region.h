#pragma once

#define region_addr_t ulong

#define _region_type(addr_t, ...) \
struct __VA_ARGS__ \
{ \
	addr_t beg, end; \
}

#define region_valid(reg)	((reg)->beg < (reg)->end)
#define region_size(reg)	((reg)->end - (reg)->beg)
