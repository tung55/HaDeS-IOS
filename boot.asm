BITS 32
section .multiboot
align 4
    dd 0x1BADB002
    dd 0x00000003
    dd -(0x1BADB002 + 0x00000003)

section .bss
align 16
stack_bottom:
    resb 16384
stack_top:

section .text
global _start
extern kernel_main
_start:
    mov esp, stack_top
    ; Đẩy tham số vào stack đúng chuẩn C (từ phải sang trái)
    push eax     ; Tham số 2 (Magic)
    push ebx     ; Tham số 1 (Multiboot ptr)
    call kernel_main
.hang:
    cli
    hlt
    jmp .hang
