; Using 32-bit protected mode
[bits 32]

; This is how constants are defined
VIDEO_MEMORY equ 0xb8000
; The color byte for each character
WHITE_ON_BLACK equ 0x0f

printStringProtectedMode:
    pusha
    mov edx, VIDEO_MEMORY

printStringProtectedModeLoop:
    ; [ebx] is the address of our character
    mov al, [ebx]
    mov ah, WHITE_ON_BLACK

    ; Check if end of string
    cmp al, 0
    je printStringProtectedModeDone

    ; Store character + attribute in video memory
    mov [edx], ax
    ; Next char
    add ebx, 1
    ; Next video memory position
    add edx, 2

    jmp printStringProtectedModeLoop

printStringProtectedModeDone:
    popa
    ret