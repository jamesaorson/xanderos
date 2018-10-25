[bits 32]
; Define calling point. Must have same name as kernel.c 'main' function
[extern main]

; Calls the C function. The linker will know where it is placed in memory
call main
jmp $