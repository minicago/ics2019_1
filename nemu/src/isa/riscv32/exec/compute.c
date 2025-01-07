#include "cpu/exec.h"

make_EHelper(lui) {
  rtl_sr(id_dest->reg, &id_src->val, 4);

  print_asm_template2(lui);
}

make_EHelper(addi){
  rtl_addi(id_dest, &id_src->val, id_src->imm);
  print_asm_template2(addi);
}