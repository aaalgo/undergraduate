.global main
.text
main:
ljmp $0xABCD, $0x12345678
lcall $0xABCD, $0x12345678
ret

