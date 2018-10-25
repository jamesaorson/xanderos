[org 0x7c00]
; The same one we used when linking the kernel
KERNEL_OFFSET equ 0x1000

    ; Remember that the BIOS sets us the boot drive in 'dl' on boot
    mov [BOOT_DRIVE], dl
    mov bp, 0x9000
    mov sp, bp

    mov bx, MSG_REAL_MODE 
    call print
    call print_newline

    ; read the kernel from disk
    call load_kernel
    ; disable interrupts, load GDT,  etc. Finally jumps to 'BEGIN_PM'
    call switch_to_protected_mode
    ; Never executed
    jmp $

%include "src/helpers/print.asm"
%include "src/helpers/print_hex.asm"
%include "src/boot_disk.asm"
%include "src/32_bit_gdt.asm"
%include "src/helpers/32_bit_print.asm"
%include "src/32_bit_switch.asm"

[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print
    call print_newline

    mov bx, KERNEL_OFFSET ; Read from disk and store in 0x1000
    mov dh, 2
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
BEGIN_PROTECTED_MODE:
    mov ebx, MSG_PROTECTED_MODE
    call print_string_protected_mode
    call KERNEL_OFFSET ; Give control to the kernel
    jmp $ ; Stay here when the kernel returns control to us (if ever)


BOOT_DRIVE db 0 ; It is a good idea to store it in memory because 'dl' may get overwritten
MSG_REAL_MODE db "Started in 16-bit Real Mode", 0
MSG_PROTECTED_MODE db "Landed in 32-bit Protected Mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0

; padding
times 510 - ($-$$) db 0
dw 0xaa55