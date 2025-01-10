#include "cpu/exec.h"

make_EHelper(ecall){
    raise_intr(reg_l(17), *pc);
}

make_EHelper(CSRRW){
    Log("%x",*CSR(id_src2->val));
    rtl_li (&reg_l(id_dest)  , *CSR(id_src2->val));
    *CSR(id_src2->val) = id_src->val;
}
make_EHelper(CSRRS){
    Log("%x",*CSR(id_src2->val));
    
    rtl_li (&reg_l(id_dest) , *CSR(id_src2->val));
    Log("%x",reg_l(id_dest->reg));
    *CSR(id_src2->val) |= id_src->val;
}
make_EHelper(CSRRC){
    Log("%x",*CSR(id_src2->val));
    rtl_li (&reg_l(id_dest) , *CSR(id_src2->val));
    *CSR(id_src2->val) |= ~id_src->val;
}