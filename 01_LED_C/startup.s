; file:         startup.s
; author:       秦殇 (ywz_123xxx@163.com)
; brief:        stm32L475 asm startup file
; version:      0.1
; date:         2020-11-14
; copyright:    Copyright (c) 2020

                PRESERVE8
                THUMB

; 异常向量表, 必须放在 ROM 上, 
; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
;; CPU上电之后 强制跳转到此处执行函数
__Vectors       DCD     0
                DCD     Reset_Handler              ; Reset Handler
                
                AREA    |.text|, CODE, READONLY

; Reset handler
Reset_Handler    PROC
                 EXPORT  Reset_Handler             [WEAK]
                 IMPORT  mymain

                 LDR sp, = (0x20000000+0x18000)
                 BL     mymain
                 ENDP


                 END

;************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE*****
