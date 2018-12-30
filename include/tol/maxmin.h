#pragma once

#ifndef MAX
#define MAX(x, y)	((x)>(y)?(x):(y))
#endif
#ifndef MIN
#define MIN(x, y)	((x)<(y)?(x):(y))
#endif
#ifndef CLAMP
#define CLAMP(x, max, min)	MAX(min, MIN(x, max))
#endif
