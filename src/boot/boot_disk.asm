; Load 'dh' sectors from drive 'dl' into ES:BX
disk_load:
    pusha
    ; Reading from disk requires setting specific values in all registers
    ; so we will overwrite our input parameters from 'dx'. Let's save it
    ; to the stack for later use.
    push dx

    ; ah <- int 0x13 function. 0x02 = 'read'
    mov ah, 0x02
    ; al <- number of sectors to read (0x01 .. 0x80)
    mov al, dh
    ; cl <- sector (0x01 .. 0x11)
    ; 0x01 is our boot sector, 0x02 is the first 'available' sector
    mov cl, 0x02
    ; ch <- cylinder (0x0 .. 0x3FF, upper 2 bits in 'cl')
    ; dl <- drive number. Our caller sets it as a parameter and gets it from BIOS
    ; (0 = floppy, 1 = floppy2, 0x80 = hdd, 0x81 = hdd2)
    mov ch, 0x00
    ; dh <- head number (0x0 .. 0xF)
    mov dh, 0x00

    ; [es:bx] <- pointer to buffer where the data will be stored
    ; caller sets it up for us, and it is actually the standard location for int 13h
    
    ; BIOS interrupt
    int 0x13
    ; if error (stored in the carry bit)
    jc disk_error

    pop dx
    ; BIOS also sets 'al' to the # of sectors read. Compare it.
    cmp al, dh
    jne sectors_error
    popa
    ret

disk_error:
    mov bx, DISK_ERROR
    call print
    call print_newline
    ; ah = error code, dl = disk drive that dropped the error
    mov dh, ah
    ; check out the code at http://stanislavs.org/helppc/int_13-1.html
    call print_hex
    jmp disk_loop

sectors_error:
    mov bx, SECTORS_ERROR
    call print

disk_loop:
    mov bx, DISK_LOADED
    call print
    
    jmp $

DISK_ERROR: db "Disk read error", 0
SECTORS_ERROR: db "Incorrect number of sectors read", 0

DISK_LOADED: db "Welcome to XanderOS", 0