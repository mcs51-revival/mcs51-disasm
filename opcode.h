/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright(c) 2021 Sanpe <sanpeqf@gmail.com>
 */

#ifndef _OPCODE_H_
#define _OPCODE_H_

#include <stdint.h>

enum mcs51_format { /* MCS-51 format table              */
    MCS51_INS_NON,      /* ins                          */
    MCS51_INS_A11,      /* ins  addr11                  */
    MCS51_INS_A16,      /* ins  addr16                  */

    MCS51_INS_ACC,      /* ins  a                       */
    MCS51_INS_ACB,      /* ins  ab                      */
    MCS51_INS_ACR,      /* ins  a, reg                  */
    MCS51_INS_ATR,      /* ins  a, @reg                 */
    MCS51_INS_ACI,      /* ins  a, #immed               */
    MCS51_INS_AIO,      /* ins  a, #immed, offset       */
    MCS51_INS_ACD,      /* ins  a, direct               */
    MCS51_INS_ADO,      /* ins  a, direct, offset       */
    MCS51_INS_ATP,      /* ins  a, @dptr                */
    MCS51_INS_ATA,      /* ins  a, @a+dptr              */
    MCS51_INS_ATC,      /* ins  a, @a+pc                */

    MCS51_INS_REG,      /* ins  reg                     */
    MCS51_INS_REA,      /* ins  reg, a                  */
    MCS51_INS_REI,      /* ins  reg, #immed             */
    MCS51_INS_RIO,      /* ins  reg, #immed, offset     */
    MCS51_INS_RED,      /* ins  reg, direct             */
    MCS51_INS_REO,      /* ins  reg, offset             */

    MCS51_INS_DIR,      /* ins  direct                  */
    MCS51_INS_DIA,      /* ins  direct, a               */
    MCS51_INS_DRE,      /* ins  direct, reg             */
    MCS51_INS_DTR,      /* ins  direct, @reg            */
    MCS51_INS_DII,      /* ins  direct, #immed          */
    MCS51_INS_DID,      /* ins  direct, direct          */
    MCS51_INS_DIO,      /* ins  direct, offset          */

    MCS51_INS_PTR,      /* ins  dptr                    */
    MCS51_INS_PTI,      /* ins  dptr, #immed            */

    MCS51_INS_BIT,      /* ins  bit                     */
    MCS51_INS_BIC,      /* ins  bit, c                  */
    MCS51_INS_BIO,      /* ins  bit, offset             */

    MCS51_INS_CON,      /* ins  c                       */
    MCS51_INS_COB,      /* ins  c, bit                  */
    MCS51_INS_COX,      /* ins  c, /bit                 */

    MCS51_INS_TRE,      /* ins  @reg                    */
    MCS51_INS_TRA,      /* ins  @reg, a                 */
    MCS51_INS_TRI,      /* ins  @reg, #immed            */
    MCS51_INS_TIO,      /* ins  @reg, #immed, offset    */
    MCS51_INS_TRD,      /* ins  @reg, direct            */

    MCS51_INS_TPA,      /* ins  @dptr, a                */
    MCS51_INS_TAD,      /* ins  @a+dptr                 */
    MCS51_INS_TPI,      /* ins  @dptr, #immed           */

    MCS51_INS_OFF,      /* ins  offset                  */
};

struct mcs51_ops {
    uint8_t opcode;
    uint8_t mask;
    uint8_t reg;
    unsigned int min;
    unsigned int max;
    unsigned int size;
    enum mcs51_format format;
    const char *name;
};

static const char *mcs51_reg_name[] = {
    "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7",
};

static const char *mcs51_treg_name[] = {
    "@r0", "@r1"
};

static const struct mcs51_ops mcs51_table[] = {
    { 0x00, 0xff, 0x00, 0x0, 0x0, 1, MCS51_INS_NON, "nop"},     /* nop                              */
    { 0x01, 0x1f, 0x00, 0x0, 0x0, 2, MCS51_INS_A11, "ajmp"},    /* ajmp     addr11                  */
    { 0x02, 0xff, 0x00, 0x0, 0x0, 3, MCS51_INS_A16, "ljmp"},    /* ljmp     addr16                  */
    { 0x03, 0xff, 0x00, 0x0, 0x0, 1, MCS51_INS_ACC, "rr"},      /* rr       a                       */
    { 0x04, 0xff, 0x00, 0x0, 0x0, 1, MCS51_INS_ACC, "inc"},     /* inc      a                       */
    { 0x05, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_DIR, "inc"},     /* inc      direct                  */
    { 0x06, 0xf0, 0x0f, 0x6, 0x7, 1, MCS51_INS_TRE, "inc"},     /* inc      @reg                    */
    { 0x08, 0xf0, 0x0f, 0x8, 0xf, 1, MCS51_INS_REG, "inc"},     /* inc      reg                     */

    { 0x10, 0xff, 0x00, 0x0, 0x0, 3, MCS51_INS_BIO, "jbc"},     /* jbc      bit, offset             */
    { 0x11, 0x1f, 0x00, 0x0, 0x0, 2, MCS51_INS_A11, "acall"},   /* acall    addr11                  */
    { 0x12, 0xff, 0x00, 0x0, 0x0, 3, MCS51_INS_A16, "lcall"},   /* lcall    addr16                  */
    { 0x13, 0xff, 0x00, 0x0, 0x0, 1, MCS51_INS_ACC, "rrc"},     /* rrc      a                       */
    { 0x14, 0xff, 0x00, 0x0, 0x0, 1, MCS51_INS_ACC, "dec"},     /* dec      a                       */
    { 0x15, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_DIR, "dec"},     /* dec      direct                  */
    { 0x16, 0xf0, 0x0f, 0x6, 0x7, 1, MCS51_INS_TRE, "dec"},     /* dec      @reg                    */
    { 0x18, 0xf0, 0x0f, 0x8, 0xf, 1, MCS51_INS_REG, "dec"},     /* dec      reg                     */

    { 0x20, 0xff, 0x00, 0x0, 0x0, 3, MCS51_INS_BIO, "jb"},      /* jb       bit, offset             */
    { 0x22, 0xff, 0x00, 0x0, 0x0, 1, MCS51_INS_NON, "ret"},     /* ret                              */
    { 0x23, 0xff, 0x00, 0x0, 0x0, 1, MCS51_INS_ACC, "rl"},      /* rl       a                       */
    { 0x24, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_ACI, "add"},     /* add      a, #immed               */
    { 0x25, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_ACD, "add"},     /* add      a, direct               */
    { 0x26, 0xf0, 0x0f, 0x6, 0x7, 1, MCS51_INS_ATR, "add"},     /* add      a, @reg                 */
    { 0x28, 0xf0, 0x0f, 0x8, 0xf, 1, MCS51_INS_ACR, "add"},     /* add      a, reg                  */

    { 0x30, 0xff, 0x00, 0x0, 0x0, 3, MCS51_INS_BIO, "jnb"},     /* jnb      bit, offset             */
    { 0x32, 0xff, 0x00, 0x0, 0x0, 1, MCS51_INS_NON, "reti"},    /* reti                             */
    { 0x33, 0xff, 0x00, 0x0, 0x0, 1, MCS51_INS_ACC, "rlc"},     /* rlc      a                       */
    { 0x34, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_ACI, "addc"},    /* addc     a, #immed               */
    { 0x35, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_ACD, "addc"},    /* addc     a, direct               */
    { 0x36, 0xf0, 0x0f, 0x6, 0x7, 1, MCS51_INS_ATR, "addc"},    /* addc     a, @reg                 */
    { 0x38, 0xf0, 0x0f, 0x8, 0xf, 1, MCS51_INS_ACR, "addc"},    /* addc     a, reg                  */

    { 0x40, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_OFF, "jc"},      /* jc       offset                  */
    { 0x42, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_DIA, "orl"},     /* orl      direct, a               */
    { 0x43, 0xff, 0x00, 0x0, 0x0, 3, MCS51_INS_DII, "orl"},     /* orl      direct, #immed          */
    { 0x44, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_ACI, "orl"},     /* orl      a, #immed               */
    { 0x45, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_ACD, "orl"},     /* orl      a, direct               */
    { 0x46, 0xf0, 0x0f, 0x6, 0x7, 1, MCS51_INS_ATR, "orl"},     /* orl      a, @reg                 */
    { 0x48, 0xf0, 0x0f, 0x8, 0xf, 1, MCS51_INS_ACR, "orl"},     /* orl      a, reg                  */

    { 0x50, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_OFF, "jnc"},     /* jnc      offset                  */
    { 0x52, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_DIA, "anl"},     /* anl      direct, a               */
    { 0x53, 0xff, 0x00, 0x0, 0x0, 3, MCS51_INS_DII, "anl"},     /* anl      direct, #immed          */
    { 0x54, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_ACI, "anl"},     /* anl      a, #immed               */
    { 0x55, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_ACD, "anl"},     /* anl      a, direct               */
    { 0x56, 0xf0, 0x0f, 0x6, 0x7, 1, MCS51_INS_ATR, "anl"},     /* anl      a, @reg                 */
    { 0x58, 0xf0, 0x0f, 0x8, 0xf, 1, MCS51_INS_ACR, "anl"},     /* anl      a, reg                  */

    { 0x60, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_OFF, "jz"},      /* jz       offset                  */
    { 0x62, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_DIA, "xrl"},     /* xrl      direct, a               */
    { 0x63, 0xff, 0x00, 0x0, 0x0, 3, MCS51_INS_DII, "xrl"},     /* xrl      direct, #immed          */
    { 0x64, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_ACI, "xrl"},     /* xrl      a, #immed               */
    { 0x65, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_ACD, "xrl"},     /* xrl      a, direct               */
    { 0x66, 0xf0, 0x0f, 0x6, 0x7, 1, MCS51_INS_ATR, "xrl"},     /* xrl      a, @reg                 */
    { 0x68, 0xf0, 0x0f, 0x8, 0xf, 1, MCS51_INS_ACR, "xrl"},     /* xrl      a, reg                  */

    { 0x70, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_OFF, "jnz"},     /* jnz      offset                  */
    { 0x72, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_COB, "orl"},     /* orl      c, bit                  */
    { 0x73, 0xff, 0x00, 0x0, 0x0, 1, MCS51_INS_TAD, "jmp"},     /* jmp      @a+dptr                 */
    { 0x74, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_ACI, "mov"},     /* mov      a, #immed               */
    { 0x75, 0xff, 0x00, 0x0, 0x0, 3, MCS51_INS_DII, "mov"},     /* mov      direct, #immed          */
    { 0x76, 0xf0, 0x0f, 0x6, 0x7, 2, MCS51_INS_TRI, "mov"},     /* mov      @reg, #immed            */
    { 0x78, 0xf0, 0x0f, 0x8, 0xf, 2, MCS51_INS_REI, "mov"},     /* mov      reg, #immed             */

    { 0x80, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_OFF, "sjmp"},    /* sjmp     offset                  */
    { 0x82, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_COB, "anl"},     /* anl      c, bit                  */
    { 0x83, 0xff, 0x00, 0x0, 0x0, 1, MCS51_INS_ATC, "movc"},    /* movc     a, @a+pc                */
    { 0x84, 0xff, 0x00, 0x0, 0x0, 1, MCS51_INS_ACB, "div"},     /* div      ab                      */
    { 0x85, 0xff, 0x00, 0x0, 0x0, 3, MCS51_INS_DID, "mov"},     /* mov      direct, direct          */
    { 0x86, 0xf0, 0x0f, 0x6, 0x7, 2, MCS51_INS_DTR, "mov"},     /* mov      direct, @reg            */
    { 0x88, 0xf0, 0x0f, 0x8, 0xf, 2, MCS51_INS_DRE, "mov"},     /* mov      direct, reg             */

    { 0x90, 0xff, 0x00, 0x0, 0x0, 3, MCS51_INS_PTI, "mov"},     /* mov      dptr, #immed            */
    { 0x92, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_BIC, "mov"},     /* mov      bit, c                  */
    { 0x93, 0xff, 0x00, 0x0, 0x0, 1, MCS51_INS_ATA, "movc"},    /* movc     a, @a+dptr              */
    { 0x94, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_ACI, "subb"},    /* subb     a, #immed               */
    { 0x95, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_ACD, "subb"},    /* subb     a, direct               */
    { 0x96, 0xf0, 0x0f, 0x6, 0x7, 1, MCS51_INS_ATR, "subb"},    /* subb     a, @reg                 */
    { 0x98, 0xf0, 0x0f, 0x8, 0xf, 1, MCS51_INS_ACR, "subb"},    /* subb     a, reg                  */

    { 0xa0, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_COX, "orl"},     /* orl      c, /bit                 */
    { 0xa2, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_COB, "mov"},     /* mov      c, bit                  */
    { 0xa3, 0xff, 0x00, 0x0, 0x0, 1, MCS51_INS_PTR, "inc"},     /* inc      dptr                    */
    { 0xa4, 0xff, 0x00, 0x0, 0x0, 1, MCS51_INS_ACB, "mul"},     /* mul      ab                      */
    { 0xa6, 0xf0, 0x0f, 0x0, 0x0, 2, MCS51_INS_TRD, "mov"},     /* mov      @reg, direct            */
    { 0xa8, 0xf0, 0x0f, 0x0, 0x0, 2, MCS51_INS_RED, "mov"},     /* mov      reg, direct             */

    { 0xb0, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_COX, "anl"},     /* anl      c, /bit                 */
    { 0xb2, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_BIT, "cpl"},     /* cpl      bit                     */
    { 0xb3, 0xff, 0x00, 0x0, 0x0, 1, MCS51_INS_CON, "cpl"},     /* cpl      c                       */
    { 0xb4, 0xff, 0x00, 0x0, 0x0, 3, MCS51_INS_AIO, "cjne"},    /* cjne     a, #immed, offset       */
    { 0xb5, 0xff, 0x00, 0x0, 0x0, 3, MCS51_INS_ADO, "cjne"},    /* cjne     a, direct, offset       */
    { 0xb6, 0xf0, 0x0f, 0x6, 0x7, 3, MCS51_INS_TIO, "cjne"},    /* cjne     @reg, #immed, offset    */
    { 0xb8, 0xf0, 0x0f, 0x8, 0xf, 3, MCS51_INS_RIO, "cjne"},    /* cjne     reg, #immed, offset     */

    { 0xc0, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_DIR, "push"},    /* push     direct                  */
    { 0xc2, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_BIT, "clr"},     /* clr      bit                     */
    { 0xc3, 0xff, 0x00, 0x0, 0x0, 1, MCS51_INS_CON, "clr"},     /* clr      c                       */
    { 0xc4, 0xff, 0x00, 0x0, 0x0, 1, MCS51_INS_ACC, "swap"},    /* swap     a                       */
    { 0xc5, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_ACD, "xch"},     /* xch      a, direct               */
    { 0xc6, 0xf0, 0x0f, 0x6, 0x7, 1, MCS51_INS_ATR, "xch"},     /* xch      a, @reg                 */
    { 0xc8, 0xf0, 0x0f, 0x8, 0xf, 1, MCS51_INS_ACR, "xch"},     /* xch      a, reg                  */

    { 0xd0, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_DIR, "pop"},     /* pop      direct                  */
    { 0xd2, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_BIT, "setb"},    /* setb     bit                     */
    { 0xd3, 0xff, 0x00, 0x0, 0x0, 1, MCS51_INS_CON, "setb"},    /* setb     c                       */
    { 0xd4, 0xff, 0x00, 0x0, 0x0, 1, MCS51_INS_ACC, "da"},      /* da       a                       */
    { 0xd5, 0xff, 0x00, 0x0, 0x0, 3, MCS51_INS_DIO, "djnz"},    /* djnz     direct, offset          */
    { 0xd6, 0xf0, 0x0f, 0x6, 0x7, 1, MCS51_INS_ATR, "xchd"},    /* xchd     a, @reg                 */
    { 0xd8, 0xf0, 0x0f, 0x8, 0xf, 2, MCS51_INS_REO, "djnz"},    /* djnz     reg, offset             */

    { 0xe0, 0xff, 0x00, 0x0, 0x0, 1, MCS51_INS_ATP, "movx"},    /* movx     a, @dptr                */
    { 0xe2, 0xfc, 0x03, 0x2, 0x3, 1, MCS51_INS_ACR, "movx"},    /* movx     a, @reg                 */
    { 0xe4, 0xff, 0x00, 0x0, 0x0, 1, MCS51_INS_ACC, "clr"},     /* clr      a                       */
    { 0xe5, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_ACD, "mov"},     /* mov      a, direct               */
    { 0xe6, 0xf0, 0x0f, 0x6, 0x7, 1, MCS51_INS_ATR, "mov"},     /* mov      a, @reg                 */
    { 0xe8, 0xf0, 0x0f, 0x8, 0xf, 1, MCS51_INS_ACR, "mov"},     /* mov      a, reg                  */

    { 0xf0, 0xff, 0x00, 0x0, 0x0, 1, MCS51_INS_TPA, "movx"},    /* movx     @dptr, a                */
    { 0xf2, 0xfc, 0x03, 0x2, 0x3, 1, MCS51_INS_TRA, "movx"},    /* movx     @reg, a                 */
    { 0xf4, 0xff, 0x00, 0x0, 0x0, 1, MCS51_INS_ACC, "cpl"},     /* cpl      a                       */
    { 0xf5, 0xff, 0x00, 0x0, 0x0, 2, MCS51_INS_DIA, "mov"},     /* mov      direct, a               */
    { 0xf6, 0xf0, 0x0f, 0x6, 0x7, 1, MCS51_INS_TRA, "mov"},     /* mov      @reg, a                 */
    { 0xf8, 0xf0, 0x0f, 0x8, 0xf, 1, MCS51_INS_REA, "mov"},     /* mov      reg, a                  */
};

#define MCS51_A11(data, ops)        ((((data)[0] & 0xe0) << 3) | (data)[1])
#define MCS51_A16(data, ops)        (((data)[1] << 8) | (data)[2])
#define MCS51_REG(data, ops)        ((((data)[0] & ~(ops)->mask) - (ops)->min))

#endif  /* _OPCODE_H_ */
