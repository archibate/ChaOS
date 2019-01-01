#include <asm/iframe.h>
#include <x86/excpvecs.h>
#include <panic.h>
#include <ccutils.h>

#include "excpdoes.inl"
const excp_vec_t excp_vecs[NEXCPS] = {
#include "excpvecs.inl"
};
