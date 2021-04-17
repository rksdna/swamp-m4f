/*
 * Swamp - cooperative multitasking operating system
 * Copyright (c) 2021 rksdna
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stm32/usart.h>
#include <stm32/gpio.h>
#include <stm32/rcc.h>
#include <threads.h>
#include <timers.h>
#include <debug.h>
#include <tools.h>
#include "board.h"

static void debug_put(void *data, char value)
{
    while (~USART1->SR & USART_SR_TXE)
        continue;

    USART1->DR = value;
}

struct stream debug_stream = {debug_put, 0};

void startup_board_401(void)
{
    /*FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY_72MHz;

    RCC->CFGR = RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL_MUL9 | RCC_CFGR_PPRE1_2;
    RCC->CR = RCC_CR_HSION | RCC_CR_HSEON;
    wait_for(&RCC->CR, RCC_CR_HSERDY, RCC_CR_HSERDY);

    RCC->CR = RCC_CR_HSION | RCC_CR_HSEON | RCC_CR_PLLON | RCC_CR_CSSON;
    wait_for(&RCC->CR, RCC_CR_PLLRDY, RCC_CR_PLLRDY);

    RCC->CFGR = RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL_MUL9 | RCC_CFGR_PPRE1_2 | RCC_CFGR_SW_PLL;

    RCC->APB1ENR = RCC_APB1ENR_USBEN;
    RCC->APB2ENR = RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN;*/

    RCC->AHB1ENR = RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;
    RCC->APB1ENR = RCC_APB1ENR_SPI2EN;
    RCC->APB2ENR = RCC_APB2ENR_USART1EN;

    GPIOA->MODER = GPIO_MODER_AFO(9) | GPIO_MODER_GPO(15);
    GPIOA->AFRH = GPIO_AFRH(9, 7);

    GPIOB->MODER = GPIO_MODER_GPO(3) |
                   GPIO_MODER_GPO(6) |
                   GPIO_MODER_GPO(7) |
                   GPIO_MODER_GPO(8) |
                   GPIO_MODER_GPO(9) |
                   GPIO_MODER_GPO(12) |
                   GPIO_MODER_AFO(13) |
                   GPIO_MODER_AFO(14) |
                   GPIO_MODER_AFO(15);
    GPIOB->AFRH =
            GPIO_AFRH(13, 5) |
            GPIO_AFRH(14, 5) |
            GPIO_AFRH(15, 5);


    GPIOC->OTYPER = GPIO_OTYPER_OT14 | GPIO_OTYPER_OT15;
    GPIOC->MODER = GPIO_MODER_GPO(13) | GPIO_MODER_GPO(14) | GPIO_MODER_GPO(15);

    USART1->CR1 = USART_CR1_UE;
    USART1->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_PCE | USART_CR1_M;
    USART1->CR2 = 0;
    USART1->CR3 = 0;
    USART1->BRR = 139;

    start_timers_clock(16000);

    debug("hello\n");
}

void board_info(void)
{
  //  debug("id: %*m flash: %dKbytes\n", sizeof(DES->ID), DES->ID, DES->FSIZE & DES_FSIZE_FSIZE);
}
