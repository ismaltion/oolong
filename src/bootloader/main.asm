%include "src/bootloader/size.asm"

[org 0x7000]
    [bits 16]
    main16:
        ; init
        xor ax, ax
        mov ds, ax
        mov es, ax
        mov ss, ax

        mov [boot_drive], dl

        mov sp, stack_top
        
        xor ah, ah
        mov al, 3
        int 10h

        mov si, msg_starting
        call print16

        xor ah, ah
        int 13h

        ; check lba
        mov ah, 41h
        mov bx, 55AAh
        mov dl, [boot_drive]
        int 13h

        jc no_lba
        cmp bx, 0xAA55
        jne no_lba
        test cx, 1
        jz no_lba

        ; check memory
        call memory_check

        ; load kernel
        mov si, disk_address_packet
        mov dl, [boot_drive]

        mov ah, 42h
        int 13h
        jc read_error

        ; load gdt
        cli
        lgdt [gdt_descriptor]

        mov eax, cr0
        or eax, 1
        mov cr0, eax

        mov ax, 0x10    
        mov ds, ax
        mov es, ax
        mov ss, ax

        jmp 0x08:main32

    no_lba:
        mov si, msg_lba_fail
        call print16
        cli
        hlt
        jmp $

    memory_check:
        xor ebx, ebx
        xor ax, ax
        mov es, ax
        mov di, 0x500
        mov byte [memory_map_size], 0
    .loop:
        cmp byte [memory_map_size], 20
        jae .end
        mov eax, 0xe820
        mov edx, 0x534D4150
        mov ecx, 24
        int 15h
        jc .end
        cmp eax, 0x534D4150
        jne .end
        add di, 24
        inc byte [memory_map_size]
        cmp ebx, 0
        je .end
        jmp .loop
    .end:
        ret

    read_error:
        mov si, msg_read_fail
        call print16
        cli
        hlt
        jmp $

    print16:
        mov ah, 0x0e
    .loop:
        lodsb
        cmp al, 0
        je .end
        int 10h
        jmp .loop
    .end:
        ret

    [bits 32]
    main32:
        mov esp, stack_top

        ; check a20 line
        call check_a20
        cmp eax, 0
        je enable_a20

        mov ax, [memory_map_size]
        call 0x7e00

        hlt
        jmp $

    check_a20:
        pushad
        mov edi, 0x112345
        mov esi, 0x012345
        mov [esi], esi
        mov [edi], edi
        cmpsd
        popad
        jne .a20_on
        mov eax, 0
        ret
    .a20_on:
        mov eax, 1
        ret

    enable_a20:
        in al, 0x92
        or al, 2
        out 0x92, al

        call check_a20
        cmp eax, 0
        je .fail
        ret
    .fail:
        mov esi, msg_a20_fail
        call print
        cli
        hlt
        jmp $

    print:
        mov ebx, 0xB8000
        .loop:
            lodsb
            cmp al, 0
            je .end
            mov byte [ebx], al
            inc ebx
            mov byte [ebx], 0x07
            inc ebx
            jmp .loop
        .end:
            ret

    msg_starting:
        db "Starting Oolong...", 0
    msg_a20_fail:
        db "Boot fail: Failed to enable the A20 line.", 0
    msg_lba_fail:
        db "Boot fail: Your BIOS does not support Logical Block addressing.", 0
    msg_read_fail:
        db "Boot fail: Read error.", 0
    boot_drive:
        db 0
    memory_map_size:
        db 0

    align 4
    disk_address_packet:
        db 0x10 ; Size
        db 0 ; Always zero
        dw KERNEL_SIZE ; Number of sectors to read
        dw 0x7e00 ; Where to put it
        dw 0 ; In memory page 0
        dd 3 ; LBA bits 0-31
        dd 0 ; LBA bits 32-63

    gdt_start:
        .null:
            dd 0x0 ; 4 bytes
            dd 0x0 ; + 4 bytes = 8 bytes
        
        .kcode:
            dw 0xffff ; first 16 bits of the limit
            dw 0 ; 16 bits - first 24 bits of the base
            db 0 ; + 8 bits = 24 (from the base too)
            db 0b10011010 ; Present bit | Ring | Ring | Type | Executable | Conforming | RW | Accessed
            db 0b11001111 ; Other flags | Last 4 bits of limit
            db 0 ; Last 8 bits of the base

        .kdata:
            dw 0xffff ; first 16 bits of the limit
            dw 0 ; 16 bits - first 24 bits of the base
            db 0 ; + 8 bits = 24 (from the base too)
            db 0b10010010 ; Present bit | Ring | Ring | Type | Executable | Direction | RW | Accessed
            db 0b11001111 ; Other flags | Last 4 bits of limit
            db 0 ; Last 8 bits of the base
    gdt_end:

    gdt_descriptor:
        dw gdt_end - gdt_start -1
        dd gdt_start

times 1024 - ($ - $$) db 0

section .bss
align 16
    stack_bottom:
        resb 32768 ; 32 kb stack
    stack_top: