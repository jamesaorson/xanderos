[org 0x7c00]
; The same one we used when linking the kernel
KERNEL_OFFSET equ 0x1000

    ; Remember that the BIOS sets us the boot drive in 'dl' on boot
    mov [BOOT_DRIVE], dl
    mov bp, 0x9000
    mov sp, bp

    mov bx, MSG_REAL_MODE 
    call print
    call printNewline

    ; Read the kernel from disk
    call loadKernel
    ; Disable interrupts, load GDT, etc. Finally jumps to 'BEGIN_PROTECTED_MODE'
    call switchToProtectedMode
    ; Never executed
    jmp $

%include "src/boot/helpers/print.asm"
%include "src/boot/helpers/print_hex.asm"
%include "src/boot/disk.asm"
%include "src/boot/32_bit/gdt.asm"
%include "src/boot/helpers/32_bit/32_bit_print.asm"
%include "src/boot/32_bit/switch_protected_mode.asm"

[bits 16]
loadKernel:
    mov bx, MSG_LOAD_KERNEL
    call print
    call printNewline

    ; Read from disk and store in 0x1000
    mov bx, KERNEL_OFFSET
    ; The future kernel will be larger, make this big
    mov dh, 16
    mov dl, [BOOT_DRIVE]
    call diskLoad

    ret

[bits 32]
BEGIN_PROTECTED_MODE:
    mov ebx, MSG_PROTECTED_MODE
    call printStringProtectedMode
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