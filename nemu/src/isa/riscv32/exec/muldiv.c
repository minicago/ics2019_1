#include "cpu/exec.h"

make_EHelper(mul){
    rtl_mul_lo(R_arg);
    print_asm_template3(mul);
}
make_EHelper(mulh){
    rtl_imul_hi(R_arg);
    print_asm_template3(mulh);    
}
make_EHelper(mulhsu){
    rtl_sumul_hi(R_arg);
    print_asm_template3(mulhu);     
}
make_EHelper(mulhu){
    rtl_mul_hi(R_arg);
    print_asm_template3(mulhu);     
}