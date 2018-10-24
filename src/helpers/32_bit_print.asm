; Using 32-bit protected mode
[bits 32]

; This is how constants are defined
VIDEO_MEMORY equ 0xb8000
; The color byte for each character
WHITE_ON_BLACK equ 0x0f

print_string_protected_mode:
    pusha
    mov edx, VIDEO_MEMORY

print_string_protected_mode_loop:
    ; [ebx] is the address of our character
    mov al, [ebx]
    mov ah, WHITE_ON_BLACK

    ; Check if end of string
    cmp al, 0
    je print_string_protected_mode_done

    ; Store character + attribute in video memory
    mov [edx], ax
    ; Next char
    add ebx, 1
    ; Next video memory position
    add edx, 2

    jmp print_string_protected_mode_loop

print_string_protected_mode_done:
    popa
    ret