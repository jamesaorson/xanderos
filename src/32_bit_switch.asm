[bits 16]
switch_to_protected_mode:
    ; Disable interrupts
    cli
    ; Load the GDT descriptor
    lgdt [gdt_descriptor]
    mov eax, cr0
    ; Set 32-bit mode bit in cr0
    or eax, 0x1
    mov cr0, eax
    ; Far jump by using a different segment
    jmp CODE_SEG:init_protected_mode

[bits 32]
; We are now using 32-bit instructions
init_protected_mode:
    ; Update the segment registers
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Update the stack right at the top of the free space
    mov ebp, 0x90000
    mov esp, ebp

    ; Call a well-known label with useful code
    call BEGIN_PROTECTED_MODE