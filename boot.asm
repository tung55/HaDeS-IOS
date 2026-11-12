BITS 32
section .multiboot
align 4
    dd 0x1BADB002            ; Magic number
    dd 0x00000003            ; Flags (align, memory)
    dd -(0x1BADB002 + 0x00000003)

section .bss
align 16
stack_bottom:
    resb 16384               ; 16KB stack
stack_top:

section .text
global _start
extern kernel_main
_start:
    mov esp, stack_top
    
    ; SỬA LỖI Ở ĐÂY: Đảo ngược thứ tự push
    push eax                 ; Push tham số thứ 2 (Magic)
    push ebx                 ; Push tham số thứ 1 (Multiboot ptr)
    
    call kernel_main

.hang:
    cli
    hlt
    jmp .hang
