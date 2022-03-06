/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright(c) 2021 Sanpe <sanpeqf@gmail.com>
 */

#include "mcs51-disasm.h"
#include <unistd.h>
#include <err.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    struct stat stat;
    int fd, retval;
    void *data, *curr;

    if ((fd = open(argv[1], O_RDONLY)) < 0)
        err(-1, "Cannot open file: %s", argv[1]);

    if ((retval = fstat(fd, &stat)) < 0)
        err(retval, "file fstat err");

    curr = data = mmap(NULL, stat.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED)
        err(-1, "file mmap err");

    do {
        printf("0x%04lx:", curr - data);
        retval = print_insn_mcs51(curr);
        printf("\n");
        curr += retval;
    } while ((stat.st_size -= retval));

    return 0;
}
