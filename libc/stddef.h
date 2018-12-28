#pragma once

#ifndef NULL
#define NULL ((void *)0)
#endif
#ifndef EOF
#define EOF (-1)
#endif
#define offsetof(type, memb) ((unsigned long) &(((type *) 0)->memb))
#define ARRAY_SIZEOF(a) (sizeof(a) / sizeof((a)[0]))
#define array_sizeof(a) (sizeof(a) / sizeof((a)[0]))
