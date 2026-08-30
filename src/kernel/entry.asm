[bits 32]

global _start
global load_idt
global load_page_directory
global enable_paging
global timer_ticks
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

    load_page_directory:
        mov eax, [esp + 4]
        mov cr3, eax
        ret

    enable_paging:
        mov eax, cr0
        or eax, 0x80000000
        mov cr0, eax

        mov eax, 0xC0000000
        add esp, eax

        lea eax, [.higher_half]
        add eax, 0xC0000000
        jmp eax
    .higher_half:
        ret

    %include "src/kernel/stubs.asm"

section .data
    timer_ticks:
        dd 0

section .bss
align 16
stack_bottom:
    resb 32768 ; safer 32 kb stack
stack_top:

section .note.GNU-stack noalloc noexec nowrite progbits