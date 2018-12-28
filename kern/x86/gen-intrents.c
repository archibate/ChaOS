#include <stdio.h>

int main(void)
{
	FILE *fout = fopen("intrents.inc", "w+");
	int i;
	for (i = 0; i < 256; i++)
	{
		if (!(i == 8 || (10 <= i && i <= 14)))
			fprintf(fout, "\tNC %d\n", i);
		else
			fprintf(fout, "\tEC %d\n", i);
	}
	fclose(fout);
}
