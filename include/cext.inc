; vim: ft=nasm ai

; set to 0 for windows gcc
%if 1

%macro GLOBALC 1
	GLOBAL %1
%endmacro

%macro EXTERNC 1
	EXTERN %1
%endmacro

%else

%macro GLOBALC 1
	_%1 equ %1
	GLOBAL _%1
%endmacro

%macro EXTERNC 1
	EXTERN _%1
	%1 equ _%1
%endmacro

%endif
