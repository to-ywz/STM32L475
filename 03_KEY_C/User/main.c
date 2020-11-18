/**
 * @file main.c
 * @author  秦殇 (ywz_123xxx@163.com)
 * @brief 操作寄存器 点亮 LED
 * @version 0.1
 * @date 2020-11-14
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "stdint.h"
#include "../BSP/bsp_gpio.h"

#define LEDB_PIN (0x1 << 9)
#define KEY0_PIN (0x1 << 10)
#define KEY1_PIN (0x1 << 9)

void Delay(uint32_t ticks);

int main(void)
{
    uint32_t *RCC_AHB2_ENR = (uint32_t *)(RCC_BASE + 0x4c);
    uint32_t *GPIOE_MODER = (uint32_t *)(GPIOE_BASE + 0x00);
    uint32_t *GPIOE_OTYPER = (uint32_t *)(GPIOE_BASE + 0x04);
    uint32_t *GPIOE_OSPEEDR = (uint32_t *)(GPIOE_BASE + 0x08);
    uint32_t *GPIOE_PUPDR = (uint32_t *)(GPIOE_BASE + 0x0c);
    uint32_t *GPIOE_ODR = (uint32_t *)(GPIOE_BASE + 0x14);
    uint32_t *GPIOE_BSRR = (uint32_t *)(GPIOE_BASE + 0x18);
    uint32_t *GPIOE_BRR = (uint32_t *)(GPIOE_BASE + 0x28);

    uint32_t *GPIOD_MODER = (uint32_t *)(GPIOD_BASE + 0x00);
    uint32_t *GPIOD_OTYPER = (uint32_t *)(GPIOD_BASE + 0x04);
    uint32_t *GPIOD_OSPEEDR = (uint32_t *)(GPIOD_BASE + 0x08);
    uint32_t *GPIOD_PUPDR = (uint32_t *)(GPIOD_BASE + 0x0c);
    uint32_t *GPIOD_IDR = (uint32_t *)(GPIOD_BASE + 0x10);

    /* 使能 GPIOE GPIOD*/
    *RCC_AHB2_ENR |= (1 << 4) | (1 << 3);
    /* 配置 GPIOE9 工作模式 */
    *GPIOE_MODER &= (0x01 << (9 * 2));   // 配置 PIN9 为输出模式
    *GPIOE_OTYPER &= ~(0x01 << 9);       // 配置 PIN9 为推挽模式
    *GPIOE_OSPEEDR |= (0x03 << (9 * 2)); // 配置 PIN9 输出速度为 最高
    *GPIOE_PUPDR |= (0x01 << (9 * 2));   // 配置 PIN9 内部电阻上拉
    *GPIOE_ODR |= LEDB_PIN;              //
    /* 配置 GPIO 工作模式 */
    *GPIOD_MODER &= (0x00 << (10 * 2)) | (0x00 << (9 * 2)); // 配置 PIN10 PIN9 为输入模式
    *GPIOD_OTYPER &= ~(0x1 << 10) | (0x1 << 9);             // 配置 PIN10 PIN9 为推挽模式
    *GPIOD_PUPDR |= (0x01 << (10 * 2)) | (0x01 << (9 * 2)); // 配置 PIN10 PIN9 内部电阻上拉
                                                            // BSRR 两位 置 1,便于操作

    while (1)
    {
        if (0 == (*GPIOD_IDR & KEY0_PIN))
        {
            Delay(100);
            if (0 == (*GPIOD_IDR & KEY0_PIN))
            {
                while (0 == (*GPIOD_IDR & KEY0_PIN))
                    ;
            }
            *GPIOE_ODR ^= LEDB_PIN;
        }
        if (0 == (*GPIOD_IDR & KEY1_PIN))
        {
            Delay(100);
            if (0 == (*GPIOD_IDR & KEY1_PIN))
            {
                while (0 == (*GPIOD_IDR & KEY1_PIN))
                    ;
            }
        }
    }

    return 0;
}

void Delay(uint32_t ticks)
{
    while (ticks--)
        ;
}
