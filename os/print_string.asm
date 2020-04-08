;; print_string.asm
print_string:
    pusha
    mov ah, 0x0e                ; set teletype mode for 0x10 interrupt
print_string_beg:
    mov cx, [bx]                ; store addr w/ string
    cmp cl, 0                   ; return on terminating null
    je print_string_end

    mov al, cl                  ; print character
    int 0x10

    add bx, 1                   ; increment string address
    jmp print_string_beg        ; and start all over again
print_string_end:
    popa
    ret
