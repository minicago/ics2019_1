#include "cpu/exec.h"

make_EHelper(lui) {
  printf("ok");
  rtl_sr(id_dest->reg, &id_src->val, 4);
  print_asm_template2(lui);
}

make_EHelper(auipc) {
  rtl_addi(&reg_l(id_dest->reg), pc , id_src->simm);
  print_asm_template2(auipc);
}

#define make_ISAEHelper(name) \
  make_EHelper(name){ \
    concat(rtl_, name)(&reg_l(id_dest->reg), &id_src->val, id_src2->simm);\
    print_asm_template2(name); \
  }

#define make_IUAEHelper(name) \
  make_EHelper(name){ \
    concat(rtl_, name)(&reg_l(id_dest->reg), &id_src->val, id_src2->imm);\
    print_asm_template2(name); \
  }

make_ISAEHelper(addi)

// make_EHelper(addi){
//   rtl_addi(&reg_l(id_dest->reg), &id_src->val, id_src2->simm);
//   print_asm_template2(addi);
// }

// make_EHelper(slti){
//   rtl_slti(&reg_l(id_dest->reg), &id_src->val, id_src2->simm);
//   print_asm_template2(addi);
// }
// make_EHelper(sltiu){
//   rtl_slti(&reg_l(id_dest->reg), &id_src->val, id_src2->imm);
//   print_asm_template2(addi);  
// }
// make_EHelper(xori){
//   rtl_xori(&reg_l(id_dest->reg), &id_src->val, id_src2->imm);
//   print_asm_template2(addi);  
// }
// make_EHelper(ori){
//   rtl_xori(&reg_l(id_dest->reg), &id_src->val, id_src2->imm);
//   print_asm_template2(addi);    
// }
// make_EHelper(andi);
// make_EHelper(slli);
// make_EHelper(srli);
// make_EHelper(srai);

