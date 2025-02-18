.syntax unified
.cpu cortex-m3
.thumb

.global Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
    LDR r0, =_estack
    MOV sp, r0
    BL SystemInit
    BL main
    B .

.section .isr_vector, "a"
    .word _estack
    .word Reset_Handler