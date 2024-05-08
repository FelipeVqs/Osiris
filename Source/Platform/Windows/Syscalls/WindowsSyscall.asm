.CODE

syscallWrapper PROC
    ; Save non-volatile registers that we are going to modify
    push r11
    push rdi

    ; Load syscall index into rax
    mov eax, dword ptr [rcx]

    ; Check if the syscall index is valid
    cmp eax, MAX_SYSCALL_INDEX
    jae syscallWrapperEnd ; If it's not, jump to the end of the procedure

    ; Load first parameter into rdi
    mov rdi, rcx
    add rdi, 8

    ; Check if the first parameter is NULL
    cmp rdi, 0
    je syscallWrapperNullParam ; If it is, jump to the error handling code

    syscall

syscallWrapperEnd:
    ; Restore non-volatile registers
    pop rdi
    pop r11
    ret

syscallWrapperNullParam:
    ; Set error code and return
    mov eax, E_NULL_PARAM
    jmp syscallWrapperEnd

syscallWrapper ENDP

END
