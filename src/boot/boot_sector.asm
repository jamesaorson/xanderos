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

    ; Read the kernel from disk
    call load_kernel
    ; Disable interrupts, load GDT, etc. Finally jumps to 'BEGIN_PROTECTED_MODE'
    call switch_to_protected_mode
    ; Never executed
    jmp $

%include "src/helpers/print.asm"
%include "src/helpers/print_hex.asm"
%include "src/boot/boot_disk.asm"
%include "src/32_bit/32_bit_gdt.asm"
%include "src/helpers/32_bit/32_bit_print.asm"
%include "src/32_bit/32_bit_switch.asm"

[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print
    call print_newline

    ; Read from disk and store in 0x1000
    mov bx, KERNEL_OFFSET
    mov dh, 2
    mov dl, [BOOT_DRIVE]
    call disk_load

    ret

[bits 32]
BEGIN_PROTECTED_MODE:
    mov ebx, MSG_PROTECTED_MODE
    call print_string_protected_mode
    ; Give control to the kernel
    call KERNEL_OFFSET

    ; Stay here when the kernel returns control to us (if ever)
    jmp $

; It is a good idea to store it in memory because 'dl' may get overwritten
BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16-bit Real Mode", 0
MSG_PROTECTED_MODE db "Landed in 32-bit Protected Mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0

; Padding for 512 byte boot sector
times 510 - ($-$$) db 0
dw 0xaa55