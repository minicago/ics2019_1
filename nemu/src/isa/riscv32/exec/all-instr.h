#include "cpu/exec.h"

make_EHelper(lui);
make_EHelper(auipc);

make_EHelper(ld);
make_EHelper(sld);
make_EHelper(st);

make_EHelper(inv);
make_EHelper(nemu_trap);

make_EHelper(addi);
make_EHelper(slti);
make_EHelper(sltiu);
make_EHelper(xori);
make_EHelper(ori);
make_EHelper(andi);
make_EHelper(slli);
make_EHelper(shli);
make_EHelper(shri);

make_EHelper(add);
make_EHelper(shl);
make_EHelper(slt);
make_EHelper(sltu);
make_EHelper(xor);
make_EHelper(shr);
make_EHelper(or);
make_EHelper(and);

make_EHelper(B);
make_EHelper(jal);
make_EHelper(jalr);
