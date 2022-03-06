/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright(c) 2021 Sanpe <sanpeqf@gmail.com>
 */

#ifndef _MCS51_DISASM_H_
#define _MCS51_DISASM_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * ARRAY_SIZE - get the number of elements in array.
 * @arr: array to be sized.
 */
#define ARRAY_SIZE(arr) ( \
    sizeof(arr) / sizeof((arr)[0]) \
)

extern int print_insn_mcs51(uint8_t *data);

#endif  /* _MCS51_DISASM_H_ */
