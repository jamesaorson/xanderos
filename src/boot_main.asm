[org 0x7c00]
    ; Set the stack far away
    mov bp, 0x8000
    mov sp, bp

    ; es:bx = 0x0000:0x9000 = 0x09000
    mov bx, 0x9000
    ; Read 2 sectors
    mov dh, 2
    ; The bios sets 'dl' for our boot disk number
    ; If you have trouble, use the '-fda' flag: 'qemu -fda xanderos.bin'
    call disk_load

    ; Retrieve the first loaded word, 0xDADA
    mov dx, [0x9000]
    call print_hex

    call print_newline

    ; First word from second loaded sector, 0xFACE
    mov dx, [0x9000 + 512]
    call print_hex

    call print_newline

    jmp $

%include "src/helpers/print.asm"
%include "src/helpers/print_hex.asm"
%include "src/boot_disk.asm"

times 510 - ($-$$) db 0
; Kernel flad
dw 0xaa55

; Boot sector = sector 1 of cyl 0 of head 0 of hdd 0
; From now on = sector 2 ...

; Sector 2 = 512 bytes
times 256 dw 0xdada
; Sector 3 = 512 bytes
times 256 dw 0xface