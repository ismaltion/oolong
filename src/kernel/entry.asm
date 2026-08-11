[bits 32]

global _start
global load_idt
global default_irq_stub
global timer_ticks
global timer_stub
extern kmain

section .text
    _start:
        mov esp, stack_top
        
        movzx eax, al
        push eax
        call kmain
        add esp, 4

        hlt
        jmp $

    load_idt:
        mov eax, [esp + 4]
        lidt [eax]
        sti
        ret

    default_irq_stub:
        mov al, 0x20
        out 0x20, al
        iretd

    timer_stub:
        mov al, 0x20
        out 0x20, al
        inc dword [timer_ticks]
        iretd

section .data
    timer_ticks:
        dd 0

section .bss
align 16
stack_bottom:
    resb 32768 ; safer 32 kb stack
stack_top:

section .note.GNU-stack noalloc noexec nowrite progbits