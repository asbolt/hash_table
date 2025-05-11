section .text
    global hash_word

hash_word:
    push rbp
    mov rbp, rsp
    push rbx

    xor rbx, rbx
    xor rax, rax
.next:
    mov bl, byte [rdi]
    add rax, rbx
    cmp bl, 0
    je .ending
    inc rdi
    jmp .next

.ending:
    shr rax, 7
    pop rbx
    leave
    ret

    