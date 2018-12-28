void __attribute__((weak)) do_divide_error(struct iframe *iframe)
{
	panic("EXCP_DIVIDE_ERROR");
}

void __attribute__((weak)) do_debug(struct iframe *iframe)
{
	panic("EXCP_DEBUG");
}

void __attribute__((weak)) do_nmi(struct iframe *iframe)
{
	panic("EXCP_NMI");
}

void __attribute__((weak)) do_break_point(struct iframe *iframe)
{
	panic("EXCP_BREAK_POINT");
}

void __attribute__((weak)) do_overflow(struct iframe *iframe)
{
	panic("EXCP_OVERFLOW");
}

void __attribute__((weak)) do_bounds_check(struct iframe *iframe)
{
	panic("EXCP_BOUNDS_CHECK");
}

void __attribute__((weak)) do_invalid_opcode(struct iframe *iframe)
{
	panic("EXCP_INVALID_OPCODE");
}

void __attribute__((weak)) do_device_not_available(struct iframe *iframe)
{
	panic("EXCP_DEVICE_NOT_AVAILABLE");
}

void __attribute__((weak)) do_double_fault(struct iframe *iframe)
{
	panic("EXCP_DOUBLE_FAULT");
}

void __attribute__((weak)) do_coprocessor_seg_overrun(struct iframe *iframe)
{
	panic("EXCP_COPROCESSOR_SEG_OVERRUN");
}

void __attribute__((weak)) do_invalid_tss(struct iframe *iframe)
{
	panic("EXCP_INVALID_TSS");
}

void __attribute__((weak)) do_segment_not_present(struct iframe *iframe)
{
	panic("EXCP_SEGMENT_NOT_PRESENT");
}

void __attribute__((weak)) do_stack_segment(struct iframe *iframe)
{
	panic("EXCP_STACK_SEGMENT");
}

void __attribute__((weak)) do_general_protection(struct iframe *iframe)
{
	panic("EXCP_GENERAL_PROTECTION");
}

#include <x86/cregs.h>
void __attribute__((weak)) do_page_fault(struct iframe *iframe)
{
	panic("EXCP_PAGE_FAULT: cr2=%p", getcr2());
}

void __attribute__((weak)) do_reserved_exception(struct iframe *iframe)
{
	panic("EXCP_RESERVED_EXCEPTION");
}

void __attribute__((weak)) do_coprocessor_error(struct iframe *iframe)
{
	panic("EXCP_COPROCESSOR_ERROR");
}

