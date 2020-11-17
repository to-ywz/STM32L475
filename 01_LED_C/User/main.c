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
#define RCC_BASE 0x40021000UL
#define GPIOE_BASE 0x48001000UL

void Delay(uint32_t ticks);

int mymain(void)
{
    uint32_t *RCC_AHB2_ENR = (uint32_t *)(RCC_BASE + 0x4c);
    uint32_t *GPIOE_MODER = (uint32_t *)(GPIOE_BASE + 0x00);
    uint32_t *GPIO_OTYPER = (uint32_t *)(GPIOE_BASE + 0x04);
    uint32_t *GPIO_OSPEEDR = (uint32_t *)(GPIOE_BASE + 0x08);
    uint32_t *GPIO_PUPDR = (uint32_t *)(GPIOE_BASE + 0x0c);
    uint32_t *GPIO_ODR = (uint32_t *)(GPIOE_BASE + 0x14);

    /* 使能 GPIOE */
    *RCC_AHB2_ENR |= (1 << 4);
    /* 配置 GPIOE9 工作模式 */
    *GPIOE_MODER &= (0x01 << (9 * 2));  // 配置 PIN9 为输出模式
    *GPIO_OTYPER &= ~(0x01 << 9);       // 配置 PIN9 为推完模式
    *GPIO_OSPEEDR |= (0x03 << (9 * 2)); // 配置 PIN9 输出速度为 最高
    *GPIO_PUPDR |= (0x01 << (9 * 2));   // 配置 PIN9 内部电阻上拉
    // BSRR 两位 置 1,便于操作

    while (1)
    {
        *GPIO_ODR &= ~(1 << 9);
        /* 使 GPIOE 的 PIN9 输出反向电平*/
        Delay(100000);
        *GPIO_ODR |= (1 << 9);
        /* 使 GPIOE 的 PIN9 输出反向电平*/
        Delay(100000);
    }

    return 0;
}

void Delay(uint32_t ticks)
{
    while (ticks--)
        ;
}
