#include "cpu/exec.h"

make_EHelper(ecall){
    raise_intr(reg_l(17), *pc);
    // cpu.sepc = pc;
    // cpu.scause = 0x8;
    // rtl_jr(&cpu.stvec);
}

make_EHelper(CSRRW){
    rtl_li (id_dest , *CSR(id_src2->val));
    *CSR(id_src2->val) = id_src->val;
}
make_EHelper(CSRRS){
    rtl_li (id_dest , *CSR(id_src2->val));
    *CSR(id_src2->val) |= id_src->val;
}
make_EHelper(CSRRC){
    rtl_li (id_dest , *CSR(id_src2->val));
    *CSR(id_src2->val) |= ~id_src->val;
}