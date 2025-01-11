#include "cpu/exec.h"

make_EHelper(ecall){
    if(decinfo.isa.instr.rs2 == 0){
         raise_intr(reg_l(17), *pc);
    } else {
        // Log("%x",cpu.sepc);
        rtl_jr(&cpu.sepc);
    }
   
}

// make_EHelper(sret){
//     Log("%x",cpu.sepc);
//     rtl_jr(&cpu.sepc);
// }

make_EHelper(CSRRW){
    rtl_li (&reg_l(id_dest->reg)  , *CSR(id_src2->val));
    *CSR(id_src2->val) = id_src->val;
}
make_EHelper(CSRRS){
    rtl_li (&reg_l(id_dest->reg) , *CSR(id_src2->val));
    *CSR(id_src2->val) |= id_src->val;
}
make_EHelper(CSRRC){
    rtl_li (&reg_l(id_dest->reg) , *CSR(id_src2->val));
    *CSR(id_src2->val) |= ~id_src->val;
}