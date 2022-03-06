/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright(c) 2021 Sanpe <sanpeqf@gmail.com>
 */

#include "mcs51-disasm.h"
#include "opcode.h"

int print_insn_mcs51(uint8_t *data)
{
    const struct mcs51_ops *walk, *ops;
    unsigned int count, tmp;

    for (count = 0, ops = NULL; count < ARRAY_SIZE(mcs51_table); ++count) {
        walk = &mcs51_table[count];
        if ((walk->opcode ^ data[0]) & walk->mask)
            continue;

        tmp = data[0] & ~walk->mask;
        if (tmp < walk->min || walk->max < tmp)
            continue;

        ops = walk;
    }

    if (ops == NULL) {
        printf("\tbyte\t\t0x%02x", data[0]);
        return 1;
    }

    printf("\t%s", ops->name);

    switch (ops->format) {
        case MCS51_INS_NON:
            break;

        case MCS51_INS_A11:
            printf("\t\t0x%03x", MCS51_A11(data, ops));
            break;

        case MCS51_INS_A16:
            printf("\t\t0x%04x", MCS51_A16(data, ops));
            break;

        case MCS51_INS_ACC:
            printf("\t\ta");
            break;

        case MCS51_INS_ACB:
            printf("\t\tab");
            break;

        case MCS51_INS_ACR:
            printf("\t\ta, %s", mcs51_reg_name[MCS51_REG(data, ops)]);
            break;

        case MCS51_INS_ATR:
            printf("\t\ta, @%s", mcs51_treg_name[MCS51_REG(data, ops)]);
            break;

        case MCS51_INS_ACI:
            printf("\t\ta, #0x%02x", data[1]);
            break;

        case MCS51_INS_AIO:
            printf("\t\ta, #0x%02x, 0x%02x", data[1], data[2]);
            break;

        case MCS51_INS_ACD:
            printf("\t\ta, 0x%02x", data[1]);
            break;

        case MCS51_INS_ADO:
            printf("\t\ta, 0x%02x, 0x%02x", data[1], data[2]);
            break;

        case MCS51_INS_ATP:
            printf("\t\ta, @dptr");
            break;

        case MCS51_INS_ATA:
            printf("\t\ta, @a+dptr");
            break;

        case MCS51_INS_ATC:
            printf("\t\ta, @a+pc");
            break;

        case MCS51_INS_REG:
            printf("\t\t%s", mcs51_reg_name[MCS51_REG(data, ops)]);
            break;

        case MCS51_INS_REA:
            printf("\t\t%s, a", mcs51_reg_name[MCS51_REG(data, ops)]);
            break;

        case MCS51_INS_REI:
            printf("\t\t%s, #0x%02x", mcs51_reg_name[MCS51_REG(data, ops)], data[1]);
            break;

        case MCS51_INS_RIO:
            printf("\t\t%s, #0x%02x, 0x%02x", mcs51_reg_name[MCS51_REG(data, ops)], data[1], data[2]);
            break;

        case MCS51_INS_RED:
            printf("\t\t%s, 0x%02x", mcs51_reg_name[MCS51_REG(data, ops)], data[1]);
            break;

        case MCS51_INS_REO:
            printf("\t\t%s, 0x%02x", mcs51_reg_name[MCS51_REG(data, ops)], data[1]);
            break;

        case MCS51_INS_DIR:
            printf("\t\t0x%02x", data[1]);
            break;

        case MCS51_INS_DIA:
            printf("\t\t0x%02x, a", data[1]);
            break;

        case MCS51_INS_DRE:
            printf("\t\t0x%02x, %s", data[1], mcs51_reg_name[MCS51_REG(data, ops)]);
            break;

        case MCS51_INS_DTR:
            printf("\t\t0x%02x, %s", data[1], mcs51_treg_name[MCS51_REG(data, ops)]);
            break;

        case MCS51_INS_DII:
            printf("\t\t0x%02x, #0x%02x", data[1], data[2]);
            break;

        case MCS51_INS_DID:
            printf("\t\t0x%02x, 0x%02x", data[1], data[2]);
            break;

        case MCS51_INS_DIO:
            printf("\t\t0x%02x, 0x%02x", data[1], data[2]);
            break;

        case MCS51_INS_PTR:
            printf("\t\tdptr");
            break;

        case MCS51_INS_PTI:
            printf("\t\tdptr, 0x%02x", data[1]);
            break;

        case MCS51_INS_BIT:
            printf("\t\t0x%02x", data[1]);
            break;

        case MCS51_INS_BIC:
            printf("\t\t0x%02x, c", data[1]);
            break;

        case MCS51_INS_BIO:
            printf("\t\t0x%02x, 0x%02x", data[1], data[2]);
            break;

        case MCS51_INS_CON:
            printf("\t\tc");
            break;

        case MCS51_INS_COB:
            printf("\t\tc, 0x%02x", data[1]);
            break;

        case MCS51_INS_COX:
            printf("\t\tc, /0x%02x", data[1]);
            break;

        case MCS51_INS_TRE:
            printf("\t\t%s", mcs51_treg_name[MCS51_REG(data, ops)]);
            break;

        case MCS51_INS_TRA:
            printf("\t\t%s, a", mcs51_treg_name[MCS51_REG(data, ops)]);
            break;

        case MCS51_INS_TRI:
            printf("\t\t%s, #0x%02x", mcs51_treg_name[MCS51_REG(data, ops)], data[1]);
            break;

        case MCS51_INS_TIO:
            printf("\t\t%s, #0x%02x, 0x%02x", mcs51_treg_name[MCS51_REG(data, ops)], data[1], data[2]);
            break;

        case MCS51_INS_TRD:
            printf("\t\t%s, 0x%02x", mcs51_treg_name[MCS51_REG(data, ops)], data[1]);
            break;

        case MCS51_INS_TPA:
            printf("\t\t@dptr, a");
            break;

        case MCS51_INS_TAD:
            printf("\t\t@a+dptr");
            break;

        case MCS51_INS_TPI:
            printf("\t\t@dptr, #0x%02x", data[1]);
            break;

        case MCS51_INS_OFF:
            printf("\t\t0x%02x", data[1]);
            break;

        default:
            printf("\t\tundecoded operands, inst is 0x%04x", data[0]);
            break;
    }

    return ops->size;
}
