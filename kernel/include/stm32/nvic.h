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

#ifndef NVIC_H
#define NVIC_H

#include <types.h>

struct nvic
{
    volatile u32_t ISER[8];
    u32_t RESERVED0[24];
    volatile u32_t ICER[8];
    u32_t RSERVED1[24];
    volatile u32_t ISPR[8];
    u32_t RESERVED2[24];
    volatile u32_t ICPR[8];
    u32_t RESERVED3[24];
    volatile u32_t IABR[8];
    u32_t RESERVED4[56];
    volatile u8_t IP[240];
    u32_t RESERVED5[644];
    volatile u32_t STIR;
};

#define NVIC ((struct nvic *)0xE000E100)

#define NVIC_ISER_SETENA ((u32_t)0xFFFFFFFF)
#define NVIC_ISER_SETENA_0 ((u32_t)0x00000001)
#define NVIC_ISER_SETENA_1 ((u32_t)0x00000002)
#define NVIC_ISER_SETENA_2 ((u32_t)0x00000004)
#define NVIC_ISER_SETENA_3 ((u32_t)0x00000008)
#define NVIC_ISER_SETENA_4 ((u32_t)0x00000010)
#define NVIC_ISER_SETENA_5 ((u32_t)0x00000020)
#define NVIC_ISER_SETENA_6 ((u32_t)0x00000040)
#define NVIC_ISER_SETENA_7 ((u32_t)0x00000080)
#define NVIC_ISER_SETENA_8 ((u32_t)0x00000100)
#define NVIC_ISER_SETENA_9 ((u32_t)0x00000200)
#define NVIC_ISER_SETENA_10 ((u32_t)0x00000400)
#define NVIC_ISER_SETENA_11 ((u32_t)0x00000800)
#define NVIC_ISER_SETENA_12 ((u32_t)0x00001000)
#define NVIC_ISER_SETENA_13 ((u32_t)0x00002000)
#define NVIC_ISER_SETENA_14 ((u32_t)0x00004000)
#define NVIC_ISER_SETENA_15 ((u32_t)0x00008000)
#define NVIC_ISER_SETENA_16 ((u32_t)0x00010000)
#define NVIC_ISER_SETENA_17 ((u32_t)0x00020000)
#define NVIC_ISER_SETENA_18 ((u32_t)0x00040000)
#define NVIC_ISER_SETENA_19 ((u32_t)0x00080000)
#define NVIC_ISER_SETENA_20 ((u32_t)0x00100000)
#define NVIC_ISER_SETENA_21 ((u32_t)0x00200000)
#define NVIC_ISER_SETENA_22 ((u32_t)0x00400000)
#define NVIC_ISER_SETENA_23 ((u32_t)0x00800000)
#define NVIC_ISER_SETENA_24 ((u32_t)0x01000000)
#define NVIC_ISER_SETENA_25 ((u32_t)0x02000000)
#define NVIC_ISER_SETENA_26 ((u32_t)0x04000000)
#define NVIC_ISER_SETENA_27 ((u32_t)0x08000000)
#define NVIC_ISER_SETENA_28 ((u32_t)0x10000000)
#define NVIC_ISER_SETENA_29 ((u32_t)0x20000000)
#define NVIC_ISER_SETENA_30 ((u32_t)0x40000000)
#define NVIC_ISER_SETENA_31 ((u32_t)0x80000000)

#define NVIC_ICER_CLRENA ((u32_t)0xFFFFFFFF)
#define NVIC_ICER_CLRENA_0 ((u32_t)0x00000001)
#define NVIC_ICER_CLRENA_1 ((u32_t)0x00000002)
#define NVIC_ICER_CLRENA_2 ((u32_t)0x00000004)
#define NVIC_ICER_CLRENA_3 ((u32_t)0x00000008)
#define NVIC_ICER_CLRENA_4 ((u32_t)0x00000010)
#define NVIC_ICER_CLRENA_5 ((u32_t)0x00000020)
#define NVIC_ICER_CLRENA_6 ((u32_t)0x00000040)
#define NVIC_ICER_CLRENA_7 ((u32_t)0x00000080)
#define NVIC_ICER_CLRENA_8 ((u32_t)0x00000100)
#define NVIC_ICER_CLRENA_9 ((u32_t)0x00000200)
#define NVIC_ICER_CLRENA_10 ((u32_t)0x00000400)
#define NVIC_ICER_CLRENA_11 ((u32_t)0x00000800)
#define NVIC_ICER_CLRENA_12 ((u32_t)0x00001000)
#define NVIC_ICER_CLRENA_13 ((u32_t)0x00002000)
#define NVIC_ICER_CLRENA_14 ((u32_t)0x00004000)
#define NVIC_ICER_CLRENA_15 ((u32_t)0x00008000)
#define NVIC_ICER_CLRENA_16 ((u32_t)0x00010000)
#define NVIC_ICER_CLRENA_17 ((u32_t)0x00020000)
#define NVIC_ICER_CLRENA_18 ((u32_t)0x00040000)
#define NVIC_ICER_CLRENA_19 ((u32_t)0x00080000)
#define NVIC_ICER_CLRENA_20 ((u32_t)0x00100000)
#define NVIC_ICER_CLRENA_21 ((u32_t)0x00200000)
#define NVIC_ICER_CLRENA_22 ((u32_t)0x00400000)
#define NVIC_ICER_CLRENA_23 ((u32_t)0x00800000)
#define NVIC_ICER_CLRENA_24 ((u32_t)0x01000000)
#define NVIC_ICER_CLRENA_25 ((u32_t)0x02000000)
#define NVIC_ICER_CLRENA_26 ((u32_t)0x04000000)
#define NVIC_ICER_CLRENA_27 ((u32_t)0x08000000)
#define NVIC_ICER_CLRENA_28 ((u32_t)0x10000000)
#define NVIC_ICER_CLRENA_29 ((u32_t)0x20000000)
#define NVIC_ICER_CLRENA_30 ((u32_t)0x40000000)
#define NVIC_ICER_CLRENA_31 ((u32_t)0x80000000)

#define NVIC_ISPR_SETPEND ((u32_t)0xFFFFFFFF)
#define NVIC_ISPR_SETPEND_0 ((u32_t)0x00000001)
#define NVIC_ISPR_SETPEND_1 ((u32_t)0x00000002)
#define NVIC_ISPR_SETPEND_2 ((u32_t)0x00000004)
#define NVIC_ISPR_SETPEND_3 ((u32_t)0x00000008)
#define NVIC_ISPR_SETPEND_4 ((u32_t)0x00000010)
#define NVIC_ISPR_SETPEND_5 ((u32_t)0x00000020)
#define NVIC_ISPR_SETPEND_6 ((u32_t)0x00000040)
#define NVIC_ISPR_SETPEND_7 ((u32_t)0x00000080)
#define NVIC_ISPR_SETPEND_8 ((u32_t)0x00000100)
#define NVIC_ISPR_SETPEND_9 ((u32_t)0x00000200)
#define NVIC_ISPR_SETPEND_10 ((u32_t)0x00000400)
#define NVIC_ISPR_SETPEND_11 ((u32_t)0x00000800)
#define NVIC_ISPR_SETPEND_12 ((u32_t)0x00001000)
#define NVIC_ISPR_SETPEND_13 ((u32_t)0x00002000)
#define NVIC_ISPR_SETPEND_14 ((u32_t)0x00004000)
#define NVIC_ISPR_SETPEND_15 ((u32_t)0x00008000)
#define NVIC_ISPR_SETPEND_16 ((u32_t)0x00010000)
#define NVIC_ISPR_SETPEND_17 ((u32_t)0x00020000)
#define NVIC_ISPR_SETPEND_18 ((u32_t)0x00040000)
#define NVIC_ISPR_SETPEND_19 ((u32_t)0x00080000)
#define NVIC_ISPR_SETPEND_20 ((u32_t)0x00100000)
#define NVIC_ISPR_SETPEND_21 ((u32_t)0x00200000)
#define NVIC_ISPR_SETPEND_22 ((u32_t)0x00400000)
#define NVIC_ISPR_SETPEND_23 ((u32_t)0x00800000)
#define NVIC_ISPR_SETPEND_24 ((u32_t)0x01000000)
#define NVIC_ISPR_SETPEND_25 ((u32_t)0x02000000)
#define NVIC_ISPR_SETPEND_26 ((u32_t)0x04000000)
#define NVIC_ISPR_SETPEND_27 ((u32_t)0x08000000)
#define NVIC_ISPR_SETPEND_28 ((u32_t)0x10000000)
#define NVIC_ISPR_SETPEND_29 ((u32_t)0x20000000)
#define NVIC_ISPR_SETPEND_30 ((u32_t)0x40000000)
#define NVIC_ISPR_SETPEND_31 ((u32_t)0x80000000)

#define NVIC_ICPR_CLRPEND ((u32_t)0xFFFFFFFF)
#define NVIC_ICPR_CLRPEND_0 ((u32_t)0x00000001)
#define NVIC_ICPR_CLRPEND_1 ((u32_t)0x00000002)
#define NVIC_ICPR_CLRPEND_2 ((u32_t)0x00000004)
#define NVIC_ICPR_CLRPEND_3 ((u32_t)0x00000008)
#define NVIC_ICPR_CLRPEND_4 ((u32_t)0x00000010)
#define NVIC_ICPR_CLRPEND_5 ((u32_t)0x00000020)
#define NVIC_ICPR_CLRPEND_6 ((u32_t)0x00000040)
#define NVIC_ICPR_CLRPEND_7 ((u32_t)0x00000080)
#define NVIC_ICPR_CLRPEND_8 ((u32_t)0x00000100)
#define NVIC_ICPR_CLRPEND_9 ((u32_t)0x00000200)
#define NVIC_ICPR_CLRPEND_10 ((u32_t)0x00000400)
#define NVIC_ICPR_CLRPEND_11 ((u32_t)0x00000800)
#define NVIC_ICPR_CLRPEND_12 ((u32_t)0x00001000)
#define NVIC_ICPR_CLRPEND_13 ((u32_t)0x00002000)
#define NVIC_ICPR_CLRPEND_14 ((u32_t)0x00004000)
#define NVIC_ICPR_CLRPEND_15 ((u32_t)0x00008000)
#define NVIC_ICPR_CLRPEND_16 ((u32_t)0x00010000)
#define NVIC_ICPR_CLRPEND_17 ((u32_t)0x00020000)
#define NVIC_ICPR_CLRPEND_18 ((u32_t)0x00040000)
#define NVIC_ICPR_CLRPEND_19 ((u32_t)0x00080000)
#define NVIC_ICPR_CLRPEND_20 ((u32_t)0x00100000)
#define NVIC_ICPR_CLRPEND_21 ((u32_t)0x00200000)
#define NVIC_ICPR_CLRPEND_22 ((u32_t)0x00400000)
#define NVIC_ICPR_CLRPEND_23 ((u32_t)0x00800000)
#define NVIC_ICPR_CLRPEND_24 ((u32_t)0x01000000)
#define NVIC_ICPR_CLRPEND_25 ((u32_t)0x02000000)
#define NVIC_ICPR_CLRPEND_26 ((u32_t)0x04000000)
#define NVIC_ICPR_CLRPEND_27 ((u32_t)0x08000000)
#define NVIC_ICPR_CLRPEND_28 ((u32_t)0x10000000)
#define NVIC_ICPR_CLRPEND_29 ((u32_t)0x20000000)
#define NVIC_ICPR_CLRPEND_30 ((u32_t)0x40000000)
#define NVIC_ICPR_CLRPEND_31 ((u32_t)0x80000000)

#define NVIC_IABR_ACTIVE ((u32_t)0xFFFFFFFF)
#define NVIC_IABR_ACTIVE_0 ((u32_t)0x00000001)
#define NVIC_IABR_ACTIVE_1 ((u32_t)0x00000002)
#define NVIC_IABR_ACTIVE_2 ((u32_t)0x00000004)
#define NVIC_IABR_ACTIVE_3 ((u32_t)0x00000008)
#define NVIC_IABR_ACTIVE_4 ((u32_t)0x00000010)
#define NVIC_IABR_ACTIVE_5 ((u32_t)0x00000020)
#define NVIC_IABR_ACTIVE_6 ((u32_t)0x00000040)
#define NVIC_IABR_ACTIVE_7 ((u32_t)0x00000080)
#define NVIC_IABR_ACTIVE_8 ((u32_t)0x00000100)
#define NVIC_IABR_ACTIVE_9 ((u32_t)0x00000200)
#define NVIC_IABR_ACTIVE_10 ((u32_t)0x00000400)
#define NVIC_IABR_ACTIVE_11 ((u32_t)0x00000800)
#define NVIC_IABR_ACTIVE_12 ((u32_t)0x00001000)
#define NVIC_IABR_ACTIVE_13 ((u32_t)0x00002000)
#define NVIC_IABR_ACTIVE_14 ((u32_t)0x00004000)
#define NVIC_IABR_ACTIVE_15 ((u32_t)0x00008000)
#define NVIC_IABR_ACTIVE_16 ((u32_t)0x00010000)
#define NVIC_IABR_ACTIVE_17 ((u32_t)0x00020000)
#define NVIC_IABR_ACTIVE_18 ((u32_t)0x00040000)
#define NVIC_IABR_ACTIVE_19 ((u32_t)0x00080000)
#define NVIC_IABR_ACTIVE_20 ((u32_t)0x00100000)
#define NVIC_IABR_ACTIVE_21 ((u32_t)0x00200000)
#define NVIC_IABR_ACTIVE_22 ((u32_t)0x00400000)
#define NVIC_IABR_ACTIVE_23 ((u32_t)0x00800000)
#define NVIC_IABR_ACTIVE_24 ((u32_t)0x01000000)
#define NVIC_IABR_ACTIVE_25 ((u32_t)0x02000000)
#define NVIC_IABR_ACTIVE_26 ((u32_t)0x04000000)
#define NVIC_IABR_ACTIVE_27 ((u32_t)0x08000000)
#define NVIC_IABR_ACTIVE_28 ((u32_t)0x10000000)
#define NVIC_IABR_ACTIVE_29 ((u32_t)0x20000000)
#define NVIC_IABR_ACTIVE_30 ((u32_t)0x40000000)
#define NVIC_IABR_ACTIVE_31 ((u32_t)0x80000000)

#define NVIC_IP_PR ((u8_t)0xFF)

#define NVIC_STIR_INTID ((u32_t)0x000001FF)

#endif
