#include <l4/object.h>
#include <l4/o/fpage.h>
#include <l4/o/vspace.h>
#include <l4/o/tcb.h>
#include <memory.h>
#include <errno.h>
#include <assert.h>

#define _OBJARGS(...) __VA_ARGS__ *pa1, __VA_ARGS__ *pa2, __VA_ARGS__ *pa3
#define OBJARGS _OBJARGS(long)
#define PASS_OBJARGS _OBJARGS()
#define a1 (*pa1)
#define a2 (*pa2)
#define a3 (*pa3)

#define verify_callable_optr(op)
#define verify_creatable_optr(op)


static_assert(sizeof(tcb_t) < OBJ_MAX_SIZE);
static_assert(sizeof(fpage_t) < OBJ_MAX_SIZE);
static_assert(sizeof(vspace_t) < OBJ_MAX_SIZE);

long tcb_ctor(tcb_t *tcb)
{
	memset(tcb, 0, sizeof(tcb_t));
	return 0;
}

long fpage_ctor(fpage_t *fpage)
{
	memset(fpage, 0, sizeof(fpage_t));
	return 0;
}

long vspace_ctor(vspace_t *vs)
{
	memset(vs, 0, sizeof(vspace_t));
	vspace_newinit(vs);
	return 0;
}

long tcb_dtor(fpage_t *fpage)
{
	memset(fpage, 1, sizeof(fpage_t));
	return 0;
}

long fpage_dtor(fpage_t *fpage)
{
	memset(fpage, 1, sizeof(fpage_t));
	return 0;
}

long vspace_dtor(vspace_t *vs)
{
	vspace_delete(vs);
	memset(vs, 1, sizeof(vspace_t));
	return 0;
}


long tcb_meth(tcb_t *tcb, OBJARGS)
{
	return -ENOSYS;
}

long fpage_meth(fpage_t *fpage, OBJARGS)
{
	return -ENOSYS;
}

long vspace_meth(vspace_t *vs, OBJARGS)
{
	if (a1 & L4_VSPACE_MAP)
	{
		pgva_t va = PGDN(a2);
		pgoff_t off = 
		vs_map(vs, va, pte);
	}
}


typedef long object_ctor_t(obj_t *obj);
typedef long object_meth_t(void *p, OBJARGS);

static object_ctor_t *object_ctors[L4_OBJTYPES] =
{
	tcb_ctor,
	fpage_ctor,
	vspace_ctor,
};

static object_meth_t *object_ctors[L4_OBJTYPES] =
{
	tcb_meth,
	fpage_meth,
	vspace_meth,
};

long object_call(obj_t *op, OBJARGS)
{
	if (!a1) // create_object
	{
		if (otype >= L4_OBJTYPES)
			return -EINVAL;
		op->type = otype;
		verify_creatable_optr(op);
		return object_ctors[otype](&op->raw);
	}
	else // really object_call
	{
		assert(op->otype < L4_OBJTYPES);
		verify_callable_optr(op);
		return object_meths[op->otype](&op->raw, PASS_OBJARGS);
	}
}

