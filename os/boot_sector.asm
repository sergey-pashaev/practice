;; boot_sector.asm
[org 0x7c00]                ; set bios boot sector offset globally

    ; code
    mov bx, HELLO_MSG
    call print_string

    mov bx, EXIT_MSG
    call print_string

    jmp $                       ; infinite loop

%include "print_string.asm"

    ; data
HELLO_MSG:
    db 'Hello, world!', 0
EXIT_MSG:
    db 'Goodbye!', 0

    ; padding + magic bios number
    times 510-($-$$) db 0
    db 0x55
    db 0xAA
