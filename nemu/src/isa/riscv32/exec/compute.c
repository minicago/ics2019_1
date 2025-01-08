#include "cpu/exec.h"

make_EHelper(lui) {
  printf("ok");
  rtl_sr(id_dest->reg, &id_src->val, 4);
  print_asm_template2(lui);
}

make_EHelper(auipc) {
  // printf("%x\n", *pc + id_src->simm); 

  rtl_addi(&reg_l(id_dest->reg), pc , id_src->simm);
  // printf("%x %x\n",id_dest->reg, reg_l(2));
  print_asm_template2(auipc);
}

make_EHelper(addi){
  rtl_addi(&reg_l(id_dest->reg), &id_src->val, id_src2->simm);
  print_asm_template2(addi);
}