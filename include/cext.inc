; vim: ft=nasm ai

%macro GLOBALC 1
	_%1 equ %1
	GLOBAL _%1
%endmacro

%macro EXTERNC 1
	EXTERN _%1
	%1 equ _%1
%endmacro