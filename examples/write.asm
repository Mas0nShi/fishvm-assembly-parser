
LC0: .string "hello world!\r\n"
LC1: .byte 0x12
LC2: .dword 0x12121212

mov  edx, 14 ; comment 1
mov  esi, LC0
mov  edi, 01
mov rax, 1
syscall; comment 2
