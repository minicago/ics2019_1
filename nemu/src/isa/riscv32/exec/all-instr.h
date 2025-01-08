#include "cpu/exec.h"

make_EHelper(lui);
make_EHelper(auipc);

make_EHelper(ld);
make_EHelper(st);

make_EHelper(inv);
make_EHelper(nemu_trap);

make_EHelper(addi);
// make_EHelper(slti);
// make_EHelper(sltiu);
// make_EHelper(xori);
// make_EHelper(ori);
// make_EHelper(andi);
// make_EHelper(slli);
// make_EHelper(srli);
// make_EHelper(srai);

make_EHelper(jal);
make_EHelper(jalr);
