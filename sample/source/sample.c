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
    float value = 50.0f;
    struct timer timer;

    debug("fpu: hello\n");

    start_timer(&timer, 50);
    while (value > 1.0f)
    {
        value = value / 1.2f;
        wait_timer(&timer);
        debug("fpu: count {%d %3.d}\n", count++, (int)(value * 1000));
    }

    stop_timer(&timer);
    debug("fpu: bue\n");
}

void main(void)
{
    u32_t count = 0;
    float value = 0.1f;

    startup_board_401();
    debug("main: hello\n");
    board_info();

    debug("[%s] [%2s] [%6s] [%*s]\n", "abcd", "abcd", "abcd", 5, "abcd");
    debug("[%d] [%d] [%d] [%4d] [%12d] [%*d]\n", 0, 1, -1, 654321, 654321, 9, 654321);
    debug("[%d] [%d] [%d] [%4d] [%12d] [%*d]\n", 0, 1, -1, -654321, -654321, 9, -654321);
    debug("[%u] [%u] [%u] [%4u] [%12u] [%*u]\n", 0, 1, -1, 654321, 654321, 9, 654321);
    debug("[%x] [%x] [%x] [%4x] [%12x] [%*x]\n", 0, 1, -1, 654321, 654321, 9, 654321);
    debug("[%c] [%3c] [%*c]\n", '.', '.', 9, '.');

    start_thread(&thread_1, (function_t)blink, &data_1, stack_1, sizeof(stack_1));
    start_thread(&thread_2, (function_t)blink, &data_2, stack_2, sizeof(stack_2));
    start_thread(&thread_fpu, (function_t)blink_fpu, 0, stack_fpu, sizeof(stack_fpu));

    while (value < 2.0f)
    {
        value += 0.1f;
        debug("main: count {%d %3.d}\n", count++, (int)(value * 1000));
        sleep(70);
    }

    debug("main: bue\n");
    sleep(5000);
}
