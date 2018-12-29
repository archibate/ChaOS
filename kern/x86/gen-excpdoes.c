#include <stdio.h>
#include <string.h>

char *excps[] =
{
	"divide_error", "debug", "nmi", "break_point", "overflow",
	"bounds_check", "invalid_opcode", "device_not_available",
	"double_fault", "coprocessor_seg_overrun", "invalid_tss",
	"segment_not_present", "stack_segment", "general_protection",
	"page_fault", "reserved_exception", "coprocessor_error",
};

int main(void)
{
	FILE *fout = fopen("excpdoes.inl", "w+");
	FILE *fveh = fopen("excpvecnrs.inl", "w+");
	FILE *fvec = fopen("excpvecs.inl", "w+");
	int i;
	for (i = 0; i < sizeof(excps) / sizeof(excps[0]); i++)
	{
		printf("%d: %s...\n", i, excps[i]);
		fprintf(fout, "void _WEAK do_%s(struct iframe *iframe)\n{\n", excps[i]);
		fprintf(fout, "\tpanic(\"EXCP_%s\");\n}\n\n", strupr(strdup(excps[i])));
		fprintf(fveh, "#define EXCP_%s\t%d\n", strupr(strdup(excps[i])), i);
		fprintf(fvec, "\tdo_%s,\n", excps[i]);
	}
	fprintf(fveh, "#define NEXCPS\t%d\n", i);
	fclose(fout);
	fclose(fvec);
}
