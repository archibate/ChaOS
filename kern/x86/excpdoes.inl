void _WEAK do_divide_error(struct iframe *iframe)
{
	panic("EXCP_DIVIDE_ERROR");
}

void _WEAK do_debug(struct iframe *iframe)
{
	panic("EXCP_DEBUG");
}

void _WEAK do_nmi(struct iframe *iframe)
{
	panic("EXCP_NMI");
}

void _WEAK do_break_point(struct iframe *iframe)
{
	panic("EXCP_BREAK_POINT");
}

void _WEAK do_overflow(struct iframe *iframe)
{
	panic("EXCP_OVERFLOW");
}

void _WEAK do_bounds_check(struct iframe *iframe)
{
	panic("EXCP_BOUNDS_CHECK");
}

void _WEAK do_invalid_opcode(struct iframe *iframe)
{
	panic("EXCP_INVALID_OPCODE");
}

void _WEAK do_device_not_available(struct iframe *iframe)
{
	panic("EXCP_DEVICE_NOT_AVAILABLE");
}

void _WEAK do_double_fault(struct iframe *iframe)
{
	panic("EXCP_DOUBLE_FAULT");
}

void _WEAK do_coprocessor_seg_overrun(struct iframe *iframe)
{
	panic("EXCP_COPROCESSOR_SEG_OVERRUN");
}

void _WEAK do_invalid_tss(struct iframe *iframe)
{
	panic("EXCP_INVALID_TSS");
}

void _WEAK do_segment_not_present(struct iframe *iframe)
{
	panic("EXCP_SEGMENT_NOT_PRESENT");
}

void _WEAK do_stack_segment(struct iframe *iframe)
{
	panic("EXCP_STACK_SEGMENT");
}

void _WEAK do_general_protection(struct iframe *iframe)
{
	panic("EXCP_GENERAL_PROTECTION");
}

#if 0
#include <x86/cregs.h>
void _WEAK do_page_fault(struct iframe *iframe)
{
	panic("EXCP_PAGE_FAULT: cr2=%p", getcr2());
}
#else
extern void do_page_fault(struct iframe *iframe);
#endif

void _WEAK do_reserved_exception(struct iframe *iframe)
{
	panic("EXCP_RESERVED_EXCEPTION");
}

void _WEAK do_coprocessor_error(struct iframe *iframe)
{
	panic("EXCP_COPROCESSOR_ERROR");
}

