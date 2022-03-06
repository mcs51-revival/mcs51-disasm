# SPDX-License-Identifier: GPL-2.0-or-later
flags = -g -Wall -Werror
heads = mcs51-disasm.h opcode.h
objs  = mcs51-disasm.o main.o

%.o:%.c $(heads)
	@ echo -e "  \e[32mCC\e[0m	" $@
	@ gcc -o $@ -c $< -g $(flags)

mcs51-disasm: $(objs)
	@ echo -e "  \e[34mMKELF\e[0m	" $@
	@ gcc -o $@ $^ -g $(flags)

clean:
	@ rm -f $(objs) mcs51-disasm
