#include "cpu/exec.h"

make_EHelper(mul){
    LOG("mul %x %x", id_src->val, id_src2->val);
    rtl_mul_lo(R_arg);
    print_asm_template3(mul);
}
make_EHelper(mulh){
    rtl_imul_hi(R_arg);
    print_asm_template3(mulh);    
}
make_EHelper(mulhsu){
    rtl_sumul_hi(R_arg);
    print_asm_template3(mulhsu);     
}
make_EHelper(mulhu){
    rtl_mul_hi(R_arg);
    print_asm_template3(mulhu);     
}

make_EHelper(div){
    rtl_div_q(R_arg);
    print_asm_template3(div);  
}
make_EHelper(divu){
    rtl_idiv_q(R_arg);
    print_asm_template3(divu);  
}

make_EHelper(rem){
    rtl_div_r(R_arg);
    print_asm_template3(rem);  
}
make_EHelper(remu){
    rtl_idiv_r(R_arg);
    print_asm_template3(remu);  
}