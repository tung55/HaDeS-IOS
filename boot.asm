BITS 32
section .multiboot
align 4
    dd 0x1BADB002            ; Magic number
    dd 0x00000007            ; Flags (align, memory, video mode)
    dd -(0x1BADB002 + 0x00000007)
    dd 0                     ; Header addr
    dd 1024                  ; Yêu cầu chiều rộng
    dd 768                   ; Yêu cầu chiều cao
    dd 32                    ; Yêu cầu 32-bit màu

section .bss
align 16
stack_bottom:
    resb 16384               ; 16KB stack
stack_top:

section .text
global _start
extern kernel_main
_start:
    cli
    mov esp, stack_top
    push ebx                 ; Con trỏ trỏ tới multiboot_info
    push eax                 ; Magic number
    call kernel_main
.hang:
    cli
    hlt
    jmp .hang

section .note.GNU-stack noalloc noexec nowrite progbits
