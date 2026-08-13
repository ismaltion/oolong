[bits 32]

; Fault stubs
global double_fault_stub

extern KBUGCHK
double_fault_stub:
    add esp, 4
    sub esp, 12
    mov dword [esp], 2
    call KBUGCHK
.hang:
    cli
    hlt
    jmp .hang

; PIC stubs
global default_irq_stub
global timer_stub

default_irq_stub:
    mov al, 0x20
    out 0x20, al
    iretd

timer_stub:
    mov al, 0x20
    out 0x20, al
    inc dword [timer_ticks]
    iretd