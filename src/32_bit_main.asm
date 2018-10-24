; Bootloader offset
[org 0x7c00]
    ; Set the stack
    mov bp, 0x9000
    mov sp, bp

    mov bx, MSG_REAL_MODE
    ; This will be written after the BIOS messages
    call print

    call switch_to_protected_mode
    ; this will actually never be executed
    jmp $

%include "src/helpers/print.asm"
%include "src/32_bit_gdt.asm"
%include "src/helpers/32_bit_print.asm"
%include "src/32_bit_switch.asm"

[bits 32]
; After the switch we will get here
BEGIN_PROTECTED_MODE:
    mov ebx, MSG_PROTECTED_MODE
    ; Note that this will be written at the top left corner
    call print_string_protected_mode
    jmp $

MSG_REAL_MODE db "Started in 16-bit real mode", 0
MSG_PROTECTED_MODE db "Loaded 32-bit protected mode", 0

; bootsector
times 510-($-$$) db 0
dw 0xaa55