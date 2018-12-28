#pragma once

#include "excpvecnrs.inl"

struct iframe;
typedef void (*excp_vec_t)(struct iframe *);
extern excp_vec_t excp_vecs[NEXCPS];
