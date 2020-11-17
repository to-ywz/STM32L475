
                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
				EXPORT  __Vectors
					
__Vectors       DCD     0                  
                DCD     Reset_Handler              ; Reset Handler

				AREA    |.text|, CODE, READONLY

; Reset handler
Reset_Handler   PROC
				EXPORT  Reset_Handler             [WEAK]

               ;变量定义
                LDR     r8,     =(0x40021000 + 0x4c)    ;RCC_AHB2_ENR
                LDR     r7,     =(0x48001000 + 0x00)    ;GPIOE_MODER
                ADDS    r6,     r7, #4                  ;GPIO_OTYPER
                ADDS    r5,     r6, #4                  ;GPIO_OSPEEDR
                ADDS    r4,     r5, #4                  ;GPIO_PUPDR
                ADDS    r3,     r4, #8                  ;GPIO_ODR

                LDR     r0,     [r8]
                ORR     r0,     r0, #(1<<4)      ;使能GPIOE
                STR     r0,     [r8]

                LDR     r0,     [r7]
                AND     R0,     R0, #(0x01 << (9*2))    ;配置 GPIOE 为 输出模式
                STR     r0,     [r7]

                LDR     r0,     [r6]
                BIC     r0,     r0, #(0x01 << 9)      ;配置 GPIOE-PIN9 为 推挽
                STR     r0,     [r6]

                LDR     r0,     [r5]
                ORR     r0,     r0, #(0x03 << (9 * 2))   ;配置 GPIOE-PIN9 输出速度
                STR     r0,     [r5]

                LDR     r0,     [r4]
                ORR     r0,     r0, #(0x01 << (9 * 2))    ;配置内部电阻
                STR     r0,     [r4]

WHILE_1
                LDR     r0,     [r3]
                BIC     r0,     r0, #(1 << 9)
                STR     r0,     [r3]

                LDR     r0,     =200000
                BL      Delay

                LDR     r0,     [r3]
                ORR     r0,     r0, #(1 << 9)
                STR     r0,     [r3]

                LDR     r0,     =200000
                BL      Delay

                B WHILE_1
                ENDP

Delay
                subs r0, r0, #1
                bne Delay
                mov pc, lr

                END        