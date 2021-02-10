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

#ifndef FPU_H
#define FPU_H

#include <types.h>

struct fpu
{
    u32_t RESERVED0[1];
    volatile u32_t FPCCR;
    volatile u32_t FPCAR;
    volatile u32_t FPDSCR;
    volatile const u32_t MVFR0;
    volatile const u32_t MVFR1;
};

#define FPU ((struct fpu *)0xE000EF30)

#define FPU_FPCCR_ASPEN ((u32_t)0x80000000)
#define FPU_FPCCR_LSPEN ((u32_t)0x40000000)
#define FPU_FPCCR_MONRDY ((u32_t)0x00000010)
#define FPU_FPCCR_BFRDY ((u32_t)0x00000040)
#define FPU_FPCCR_MMRDY ((u32_t)0x00000020)
#define FPU_FPCCR_HFRDY ((u32_t)0x00000010)
#define FPU_FPCCR_THREAD ((u32_t)0x00000008)
#define FPU_FPCCR_USER ((u32_t)0x00000002)
#define FPU_FPCCR_LSPACT ((u32_t)0x00000001)

#define FPU_FPCAR_ADDRESS ((u32_t)0xFFFFFFFF8)

#define FPU_FPDSCR_AHP (u32_t)(0x04000000)
#define FPU_FPDSCR_DN (u32_t)(0x02000000)
#define FPU_FPDSCR_FZ (u32_t)(0x01000000)
#define FPU_FPDSCR_RMODES (u32_t)(0x00400000)

#define FPU_MVFR0_FP_ROUNDING_MODES  (u32_t)(0xF0000000)
#define FPU_MVFR0_SHORT_VECTORS  (u32_t)(0x0F000000)
#define FPU_MVFR0_SQUARE_ROOT  (u32_t)(0x00F00000)
#define FPU_MVFR0_DIVIDE  (u32_t)(0x000F0000)
#define FPU_MVFR0_FP_EXCEP_TRAPPING  (u32_t)(0x0000F000)
#define FPU_MVFR0_DOUBLE_PRECISION  (u32_t)(0x00000F00)
#define FPU_MVFR0_SINGLE_PRECISION  (u32_t)(0x000000F0)
#define FPU_MVFR0_A_SIMD_REGISTERS  (u32_t)(0x0000000F)

#define FPU_MVFR1_FP_FUSED_MAC  (u32_t)(0xF0000000)
#define FPU_MVFR1_FP_HPFP  (u32_t)(0x0F000000)
#define FPU_MVFR1_D_NAN_MODE  (u32_t)(0x000000F0)
#define FPU_MVFR1_FTZ_MODE  (u32_t)(0x0000000F)

#endif
