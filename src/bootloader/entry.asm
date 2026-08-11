[bits 16]
[org 0x7c00]

text:
    main:
        xor ax, ax
        mov ds, ax
        mov es, ax

        mov bx, 0x7000

        mov ah, 0h
        int 13h

        mov ah, 2h
        mov al, 2 ; load 2 sectors

        mov ch, 0
        mov cl, 2

        int 13h
        jc fail

        jmp 0x7000

    fail:
        mov si, msg_fail
        call print
        hlt
        jmp $

    print:
        mov ah, 0x0e
    .loop:
        lodsb
        cmp al, 0
        je .end
        int 10h
        jmp .loop
    .end:
        ret

data:
    msg_fail:
        db "[!] Fatal boot error.", 0

times 510 - ($ - $$) db 0
db 0x55, 0xAA