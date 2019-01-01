#pragma once

#define region_addr_t ulong

#define _region_type(addr_t, ...) \
struct __VA_ARGS__ \
{ \
	addr_t beg, end; \
}

#define make_region(_beg, _end)	((region_t){beg: (_beg), end: (_end)})
#define region_valid(reg)		((reg)->beg < (reg)->end)
#define region_size(reg)		((reg)->end - (reg)->beg)
#define region_in(reg, a)		((reg)->beg <= (a) && (a) < (reg)->end)
