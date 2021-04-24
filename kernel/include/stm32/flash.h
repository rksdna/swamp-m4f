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

#ifndef FLASH_H
#define FLASH_H

#include <types.h>

struct flash
{
    volatile u32_t ACR;
    volatile u32_t KEYR;
    volatile u32_t OPTKEYR;
    volatile u32_t SR;
    volatile u32_t CR;
    volatile u32_t OPTCR;
    volatile u32_t OPTCR1;
};

#define DES ((struct flash *)0x40023C00)

#define FLASH_ACR_LATENCY ((u32_t)0x0000000F)
#define FLASH_ACR_LATENCY_0WS ((u32_t)0x00000000)
#define FLASH_ACR_LATENCY_1WS ((u32_t)0x00000001)
#define FLASH_ACR_LATENCY_2WS ((u32_t)0x00000002)
#define FLASH_ACR_LATENCY_3WS ((u32_t)0x00000003)
#define FLASH_ACR_LATENCY_4WS ((u32_t)0x00000004)
#define FLASH_ACR_LATENCY_5WS ((u32_t)0x00000005)
#define FLASH_ACR_LATENCY_6WS ((u32_t)0x00000006)
#define FLASH_ACR_LATENCY_7WS ((u32_t)0x00000007)

#define FLASH_ACR_PRFTEN ((u32_t)0x00000100)
#define FLASH_ACR_ICEN ((u32_t)0x00000200)
#define FLASH_ACR_DCEN ((u32_t)0x00000400)
#define FLASH_ACR_ICRST ((u32_t)0x00000800)
#define FLASH_ACR_DCRST ((u32_t)0x00001000)
#define FLASH_ACR_BYTE0_ADDRESS ((u32_t)0x40023C00)
#define FLASH_ACR_BYTE2_ADDRESS ((u32_t)0x40023C03)

#define FLASH_SR_EOP ((u32_t)0x00000001)
#define FLASH_SR_SOP ((u32_t)0x00000002)
#define FLASH_SR_WRPERR ((u32_t)0x00000010)
#define FLASH_SR_PGAERR ((u32_t)0x00000020)
#define FLASH_SR_PGPERR ((u32_t)0x00000040)
#define FLASH_SR_PGSERR ((u32_t)0x00000080)
#define FLASH_SR_BSY ((u32_t)0x00010000)

#define FLASH_CR_PG ((u32_t)0x00000001)
#define FLASH_CR_SER ((u32_t)0x00000002)
#define FLASH_CR_MER ((u32_t)0x00000004)
#define FLASH_CR_SNB ((u32_t)0x000000F8)
#define FLASH_CR_SNB_0 ((u32_t)0x00000008)
#define FLASH_CR_SNB_1 ((u32_t)0x00000010)
#define FLASH_CR_SNB_2 ((u32_t)0x00000020)
#define FLASH_CR_SNB_3 ((u32_t)0x00000040)
#define FLASH_CR_SNB_4 ((u32_t)0x00000080)
#define FLASH_CR_PSIZE ((u32_t)0x00000300)
#define FLASH_CR_PSIZE_0 ((u32_t)0x00000100)
#define FLASH_CR_PSIZE_1 ((u32_t)0x00000200)
#define FLASH_CR_STRT ((u32_t)0x00010000)
#define FLASH_CR_EOPIE ((u32_t)0x01000000)
#define FLASH_CR_LOCK ((u32_t)0x80000000)

#define FLASH_OPTCR_OPTLOCK ((u32_t)0x00000001)
#define FLASH_OPTCR_OPTSTRT ((u32_t)0x00000002)
#define FLASH_OPTCR_BOR_LEV_0 ((u32_t)0x00000004)
#define FLASH_OPTCR_BOR_LEV_1 ((u32_t)0x00000008)
#define FLASH_OPTCR_BOR_LEV ((u32_t)0x0000000C)

#define FLASH_OPTCR_WDG_SW ((u32_t)0x00000020)
#define FLASH_OPTCR_nRST_STOP ((u32_t)0x00000040)
#define FLASH_OPTCR_nRST_STDBY ((u32_t)0x00000080)
#define FLASH_OPTCR_RDP ((u32_t)0x0000FF00)
#define FLASH_OPTCR_RDP_0 ((u32_t)0x00000100)
#define FLASH_OPTCR_RDP_1 ((u32_t)0x00000200)
#define FLASH_OPTCR_RDP_2 ((u32_t)0x00000400)
#define FLASH_OPTCR_RDP_3 ((u32_t)0x00000800)
#define FLASH_OPTCR_RDP_4 ((u32_t)0x00001000)
#define FLASH_OPTCR_RDP_5 ((u32_t)0x00002000)
#define FLASH_OPTCR_RDP_6 ((u32_t)0x00004000)
#define FLASH_OPTCR_RDP_7 ((u32_t)0x00008000)
#define FLASH_OPTCR_nWRP ((u32_t)0x0FFF0000)
#define FLASH_OPTCR_nWRP_0 ((u32_t)0x00010000)
#define FLASH_OPTCR_nWRP_1 ((u32_t)0x00020000)
#define FLASH_OPTCR_nWRP_2 ((u32_t)0x00040000)
#define FLASH_OPTCR_nWRP_3 ((u32_t)0x00080000)
#define FLASH_OPTCR_nWRP_4 ((u32_t)0x00100000)
#define FLASH_OPTCR_nWRP_5 ((u32_t)0x00200000)
#define FLASH_OPTCR_nWRP_6 ((u32_t)0x00400000)
#define FLASH_OPTCR_nWRP_7 ((u32_t)0x00800000)
#define FLASH_OPTCR_nWRP_8 ((u32_t)0x01000000)
#define FLASH_OPTCR_nWRP_9 ((u32_t)0x02000000)
#define FLASH_OPTCR_nWRP_10 ((u32_t)0x04000000)
#define FLASH_OPTCR_nWRP_11 ((u32_t)0x08000000)

#define FLASH_OPTCR1_nWRP ((u32_t)0x0FFF0000)
#define FLASH_OPTCR1_nWRP_0 ((u32_t)0x00010000)
#define FLASH_OPTCR1_nWRP_1 ((u32_t)0x00020000)
#define FLASH_OPTCR1_nWRP_2 ((u32_t)0x00040000)
#define FLASH_OPTCR1_nWRP_3 ((u32_t)0x00080000)
#define FLASH_OPTCR1_nWRP_4 ((u32_t)0x00100000)
#define FLASH_OPTCR1_nWRP_5 ((u32_t)0x00200000)
#define FLASH_OPTCR1_nWRP_6 ((u32_t)0x00400000)
#define FLASH_OPTCR1_nWRP_7 ((u32_t)0x00800000)
#define FLASH_OPTCR1_nWRP_8 ((u32_t)0x01000000)
#define FLASH_OPTCR1_nWRP_9 ((u32_t)0x02000000)
#define FLASH_OPTCR1_nWRP_10 ((u32_t)0x04000000)
#define FLASH_OPTCR1_nWRP_11 ((u32_t)0x08000000)

#endif
