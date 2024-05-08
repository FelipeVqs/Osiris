.globl SDLHook_PeepEvents_asm
.globl LoopModeGameHook_getWorldSession_asm
.globl ViewRenderHook_onRenderStart_asm

SDLHook_PeepEvents_asm:
    push %rbp    ; backup non-volatile rbp used in the original function
    mov %rsp, %rbp ; set up our own stack frame
    push %rdi    ; backup volatile registers used in the original function
    push %rsi
    push %rdx
    push %rcx
    push %r8
    sub $8, %rsp  ; allocate 8 bytes on the stack for the return address
    mov %rax, (%rsp) ; save the original return address
    call SDLHook_PeepEvents_cpp
    mov (%rsp), %rax ; restore the original return address
    add $8, %rsp  ; deallocate the 8 bytes on the stack
    pop %r8
    pop %rcx
    pop %rdx
    pop %rsi
    pop %rdi
    pop %rbp     ; restore the original rbp
    jmp *%rax    ; jump to the original function

LoopModeGameHook_getWorldSession_asm:
    push %rbp    ; backup non-volatile rbp used in the original function
    mov %rsp, %rbp ; set up our own stack frame
    push %rdi    ; backup volatile rdi used in the original function
    mov 8(%rsp), %rdi ; load return address into rdi
    call LoopModeGameHook_getWorldSession_cpp
    pop %rdi
    pop %rbp     ; restore the original rbp
    jmp *%rax    ; jump to the original function

ViewRenderHook_onRenderStart_asm:
    jmp ViewRenderHook_onRenderStart_cpp
