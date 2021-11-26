global entry

    MAGIC_NUMBER equ 0xE85250D6
    ARCH equ 0
    HEADER_SIZE equ mbend - mbhead
    CHECKSUM equ -(MAGIC_NUMBER + ARCH + HEADER_SIZE)

section .multiboot align=8
mbhead:
    dd MAGIC_NUMBER
    dd ARCH
    dd HEADER_SIZE
    dd CHECKSUM

tag_end:
    dd 0
    dd 8
mbend:
    align 8

section .text
entry:
    mov esp, stack_end
    mov eax, 0xAAAAAAAA
.loop:
    jmp .loop

section .bss align=4
stack_begin:
    resb 4096
stack_end:
