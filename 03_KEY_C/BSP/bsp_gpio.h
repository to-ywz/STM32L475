#ifndef BSP_GPIO_H_
#define BSP_GPIO_H_

#define RCC_BASE 0x40021000UL
#define GPIO_BASE 0x48000000UL
#define GPIOD_BASE (GPIO_BASE + 0x0C00UL)
#define GPIOE_BASE (GPIO_BASE + 0x1000UL)

#define LEDB_PIN (0x1 << 9)
#define KEY0_PIN (0x1 << 10)
#define KEY1_PIN (0x1 << 9)

#endif //  BSP_GPIO_H_