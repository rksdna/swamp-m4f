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

static u32_t gpsr()
{
    u32_t psr;
    asm volatile ("mrs %0, control\n" : "=r" (psr) : : );
    return psr;
}

#include "stm32/core.h"

static void blink(struct data *data)
{
    u32_t count = data->count;
    struct timer timer;

    debug("%s: hello\n", data->name);
    debug("%s: control %x\n", data->name, gpsr());

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
    int x = 50;
    struct timer timer;

    debug("fpu: hello\n");
    debug("fpu: control %x\n", gpsr());

    start_timer(&timer, 100);
    while (x > 1)
    {
        x = x / 2;
        wait_timer(&timer);
        debug("fpu: count {%d %d}\n", count++, (int)x);
    }

    stop_timer(&timer);
    debug("fpu: bue\n");
}

void main(void)
{
    u32_t count = 0;

    startup_board_401();
    debug("main: hello\n");
    debug("main: control %x\n", gpsr());

    debug("[%s] [%2s] [%6s] [%*s]\n", "abcd", "abcd", "abcd", 5, "abcd");
    debug("[%d] [%d] [%d] [%4d] [%12d] [%*d]\n", 0, 1, -1, 654321, 654321, 9, 654321);
    debug("[%d] [%d] [%d] [%4d] [%12d] [%*d]\n", 0, 1, -1, -654321, -654321, 9, -654321);
    debug("[%u] [%u] [%u] [%4u] [%12u] [%*u]\n", 0, 1, -1, 654321, 654321, 9, 654321);
    debug("[%x] [%x] [%x] [%4x] [%12x] [%*x]\n", 0, 1, -1, 654321, 654321, 9, 654321);
    debug("[%c] [%3c] [%*c]\n", '.', '.', 9, '.');

    start_thread(&thread_1, (function_t)blink, &data_1, stack_1, sizeof(stack_1));
    start_thread(&thread_2, (function_t)blink, &data_2, stack_2, sizeof(stack_2));
    start_thread(&thread_fpu, (function_t)blink_fpu, 0, stack_fpu, sizeof(stack_fpu));

    int x = 0;
    while (x < 2)
    {
        x += 0;

        debug("main: count {%d %d}\n", count++, (int)(10 * x));
        sleep(50);
    }

    debug("main: bue\n");
    sleep(10000);
}
