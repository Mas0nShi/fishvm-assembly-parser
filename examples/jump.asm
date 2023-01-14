; Peseudo code:

; char inp[8];
; while (1) {
;     read(0, inp, 1);  
; }

start:
mov rax, 0          ; set SYS_READ as SYS_CALL value
sub rsp, 8          ; allocate 8-byte space on the stack as read buffer
mov rdi, 0          ; set rdi to 0 to indicate a STDIN file descriptor
lea rsi, [rsp]      ; set const char *buf to the 8-byte space on stack
mov rdx, 1          ; set size_t count to 1 for one char
syscall
jmp start; while (1) 
