#include "cpu/exec.h"

make_EHelper(lui) {
  rtl_sr(id_dest->reg, &id_src->val, 4);

  print_asm_template2(lui);
}

make_EHelper(auipc) {
  printf("%x\n", *pc + id_src->simm);  
  rtl_li(id_dest, *pc + id_src->simm);
  printf("%x %d\n",id_dest, reg_l(2));
  print_asm_template2(auipc);
}

make_EHelper(addi){
  rtl_addi(id_dest, &id_src->val, id_src2->simm);
  print_asm_template2(addi);
}