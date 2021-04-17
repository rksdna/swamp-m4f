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

#include <threads.h>
#include <timers.h>
#include <tools.h>
#include <debug.h>
#include "board.h"


struct data
{
    const char *name;
    u32_t count;
    u32_t interval;
};

static struct thread thread_1;
static u8_t stack_1[1024];
static struct data data_1 = {"thread 1", 20, 20};

static struct thread thread_2;
static u8_t stack_2[1024];
static struct data data_2 = {"thread 2", 10, 30};

static struct thread thread_fpu;
static u8_t stack_fpu[1024];

static struct thread thread_step;
static u8_t stack_step[1024];

static struct thread thread_mag;
static u8_t stack_mag[1024];

static void blink(struct data *data)
{
    u32_t count = data->count;
    struct timer timer;

    debug("%s: hello\n", data->name);

    start_timer(&timer, data->interval);
    while (count--)
    {
        wait_timer(&timer);
        debug("%s: count {%d}\n", data->name, count);
    }

    stop_timer(&timer);
    debug("%s: bue\n", data->name);
}

static void blink_fpu(void)
{
    u32_t count = 0;
    float x = 50.0f;
    struct timer timer;

    debug("fpu: hello\n");

    start_timer(&timer, 50);
    while (x > 1.0f)
    {
        x = x / 1.2f;
        wait_timer(&timer);
        debug("fpu: count {%d %d}\n", count++, (int)(x * 10));
    }

    stop_timer(&timer);
    debug("fpu: bue\n");
}

#include "stm32/gpio.h"

static void step(void)
{
    debug("step: hello\n");
    sleep(50);
    // GPIOC->BSRR = GPIO_BSRR_BS13;

    GPIOB->BSRR = GPIO_BSRR_BS8;
    //  GPIOB->BSRR = GPIO_BSRR_BR9;

    sleep(50);
    GPIOC->BSRR = GPIO_BSRR_BS14;
    GPIOC->BSRR = GPIO_BSRR_BS15;

    sleep(10);

    GPIOA->BSRR = GPIO_BSRR_BS15;
    GPIOB->BSRR = GPIO_BSRR_BS3;
    GPIOB->BSRR = GPIO_BSRR_BS6;
    GPIOB->BSRR = GPIO_BSRR_BS7;

    while (1)
    {
        GPIOB->BSRR = GPIO_BSRR_BS8;
        yield_thread(0, 0);
        GPIOB->BSRR = GPIO_BSRR_BR8;
        yield_thread(0, 0);

        //yield_thread(0, 0);
        // yield_thread(0, 0);
        sleep(1);

    }

    debug("step: bue\n");
}

#include "stm32/spi.h"

u16_t mag_spi(u16_t data)
{
    GPIOB->BSRR = GPIO_BSRR_BR12;
    SPI2->DR = data;
    while(!(SPI2->SR & SPI_SR_RXNE))
        continue;
    data = SPI2->DR;
    GPIOB->BSRR = GPIO_BSRR_BS12;
    return data;


}

/*u16_t mag_read(u8_t address)
{
    u8_t high = mag_spi(0x8000 | ((address + 1) << 8));
    u8_t low = mag_spi(0x8000 | (address << 8));
    return (high << 8) + low;
}*/

void mag_write(u8_t address, u8_t value)
{
    u16_t data = (address << 8) | value;
    mag_spi(data);
}

u8_t mag_read(u8_t address)
{
    u16_t data = 0x8000 | (address << 8);
    data = mag_spi(data);
    return data;
}

s16_t mag_read2(u8_t address)
{
    return ((mag_read(address + 1) << 8) | mag_read(address));
}


float ApproxAtan(float z)
{
    const float n1 = 0.97239411f;
    const float n2 = -0.19194795f;
    return (n1 + n2 * z * z) * z;
}


#define PI_FLOAT     3.14159265f
#define PIBY2_FLOAT  1.5707963f

#define PI PI_FLOAT
#define PI_2 PIBY2_FLOAT

float fabsf(float s)
{
    return s < 0.0 ? -s : s;
}

float ApproxAtan2(float y, float x)
{
    if (x != 0.0f)
    {
        if (fabsf(x) > fabsf(y))
        {
            const float z = y / x;
            if (x > 0.0f)
            {
                // atan2(y,x) = atan(y/x) if x > 0
                return ApproxAtan(z);
            }
            else if (y >= 0.0f)
            {
                // atan2(y,x) = atan(y/x) + PI if x < 0, y >= 0
                return ApproxAtan(z) + PI;
            }
            else
            {
                // atan2(y,x) = atan(y/x) - PI if x < 0, y < 0
                return ApproxAtan(z) - PI;
            }
        }
        else // Use property atan(y/x) = PI/2 - atan(x/y) if |y/x| > 1.
        {
            const float z = x / y;
            if (y > 0.0f)
            {
                // atan2(y,x) = PI/2 - atan(x/y) if |y/x| > 1, y > 0
                return -ApproxAtan(z) + PI_2;
            }
            else
            {
                // atan2(y,x) = -PI/2 - atan(x/y) if |y/x| > 1, y < 0
                return -ApproxAtan(z) - PI_2;
            }
        }
    }
    else
    {
        if (y > 0.0f) // x = 0, y > 0
        {
            return PI_2;
        }
        else if (y < 0.0f) // x = 0, y < 0
        {
            return -PI_2;
        }
    }
    return 0.0f; // x,y = 0. Could return NaN instead.
}

float atan2_approximation1(float y, float x)
{
    //http://pubs.opengroup.org/onlinepubs/009695399/functions/atan2.html
    //Volkan SALMA

    const float ONEQTR_PI = PI / 4.0;
    const float THRQTR_PI = 3.0 * PI / 4.0;
    float r, angle;
    float abs_y = fabsf(y) + 1e-10f;      // kludge to prevent 0/0 condition
    if ( x < 0.0f )
    {
        r = (x + abs_y) / (abs_y - x);
        angle = THRQTR_PI;
    }
    else
    {
        r = (x - abs_y) / (x + abs_y);
        angle = ONEQTR_PI;
    }
    angle += (0.1963f * r * r - 0.9817f) * r;
    if ( y < 0.0f )
        return( -angle );     // negate if in quad III or IV
    else
        return( angle );


}


// |error| < 0.005
float atan2_approximation2( float y, float x )
{
    if ( x == 0.0f )
    {
        if ( y > 0.0f ) return PIBY2_FLOAT;
        if ( y == 0.0f ) return 0.0f;
        return -PIBY2_FLOAT;
    }
    float atan;
    float z = y/x;
    if ( fabsf( z ) < 1.0f )
    {
        atan = z/(1.0f + 0.28f*z*z);
        if ( x < 0.0f )
        {
            if ( y < 0.0f ) return atan - PI_FLOAT;
            return atan + PI_FLOAT;
        }
    }
    else
    {
        atan = PIBY2_FLOAT - z/(z*z + 0.28f);
        if ( y < 0.0f ) return atan - PI_FLOAT;
    }
    return atan;
}


#include "stm32/spi.h"

static void mag(void)
{
    debug("mag: hello\n");

    GPIOB->BSRR = GPIO_BSRR_BS12;
    SPI2->CR1 = SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_DFF;
    SPI2->CR1 |= SPI_CR1_SPE;

    sleep(5);

    mag_write(0x21, 0x0C);

    /*   mag_write(0x20, 0x70);
    mag_write(0x21, 0x60);
    mag_write(0x22, 0x03);
    mag_write(0x23, 0x0C);
    mag_write(0x24, 0x00);*/

    debug("CR1=%2x\n", mag_read(0x20));
    debug("CR2=%2x\n", mag_read(0x21));
    debug("CR3=%2x\n", mag_read(0x22));
    debug("CR4=%2x\n", mag_read(0x23));
    debug("CR5=%2x\n", mag_read(0x24));

    mag_write(0x20, 0x70);
    mag_write(0x23, 0x0C);

//[-1783, 2325] [- ]
    debug("CR1=%2x\n", mag_read(0x20));
    debug("CR2=%2x\n", mag_read(0x21));
    debug("CR3=%2x\n", mag_read(0x22));
    debug("CR4=%2x\n", mag_read(0x23));
    debug("CR5=%2x\n", mag_read(0x24));


    s16_t maxx = 2325, minx = -1783;
    s16_t maxy = 2153, miny = -1671;
    while (1)
    {
        mag_write(0x22, 0x01);
        sleep(100);
        s16_t x = mag_read2(0x28);
        /*if (x > maxx)
            maxx = x;
        if (x < minx)
            minx = x;*/

        s16_t y = mag_read2(0x2A);
        /*if (y > maxy)
            maxy = y;
        if (y < miny)
            miny = y;*/

        s16_t xr = (maxx - minx) / 2;
        s16_t xb = (maxx + minx) / 2;
        s16_t yr = (maxy - miny) / 2;
        s16_t yb = (maxy + miny) / 2;

        float fx = (float)(x - xb) / xr;
        float fy = (float)(y - yb) / yr;

        debug("H = %d [%d, %d] [%d %d]\n", (int)(atan2_approximation1(fx, fy) / PI * 180), minx, maxx, miny, maxy);

    }

    debug("mag: bue\n");
}

void main(void)
{
    u32_t count = 0;

    startup_board_401();
    debug("main: hello\n");

    debug("[%s] [%2s] [%6s] [%*s]\n", "abcd", "abcd", "abcd", 5, "abcd");
    debug("[%d] [%d] [%d] [%4d] [%12d] [%*d]\n", 0, 1, -1, 654321, 654321, 9, 654321);
    debug("[%d] [%d] [%d] [%4d] [%12d] [%*d]\n", 0, 1, -1, -654321, -654321, 9, -654321);
    debug("[%u] [%u] [%u] [%4u] [%12u] [%*u]\n", 0, 1, -1, 654321, 654321, 9, 654321);
    debug("[%x] [%x] [%x] [%4x] [%12x] [%*x]\n", 0, 1, -1, 654321, 654321, 9, 654321);
    debug("[%c] [%3c] [%*c]\n", '.', '.', 9, '.');

    /*start_thread(&thread_1, (function_t)blink, &data_1, stack_1, sizeof(stack_1));
    start_thread(&thread_2, (function_t)blink, &data_2, stack_2, sizeof(stack_2));*/
    //start_thread(&thread_fpu, (function_t)blink_fpu, 0, stack_fpu, sizeof(stack_fpu));
    //start_thread(&thread_step, (function_t)step, 0, stack_step, sizeof(stack_step));
    start_thread(&thread_mag, (function_t)mag, 0, stack_mag, sizeof(stack_mag));

    /*float x = 0.1f;
    while (x < 2.0f)
    {
        x += 0.1f;
        debug("main: count {%d %d}\n", count++, (int)(10 * x));
        sleep(70);
    }*/

    while (1)
        sleep(270);

    debug("main: bue\n");
}
