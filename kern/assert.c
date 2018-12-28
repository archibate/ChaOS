#include <assert.h>
#include <panic.h>

void NORETURN _assert(const char *expr, const char *file, int line)
{
	panic("%s:%d: assert(%s) failed", file, line, expr);
}
