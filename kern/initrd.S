.section .sigma0.data

	.code32

	.globl sigma0_beg, sigma0_end

sigma0_beg:
	.incbin "../sigma0/sigma0.bin"
sigma0_end:
