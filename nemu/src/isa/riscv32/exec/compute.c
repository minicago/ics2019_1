#include "cpu/exec.h"

make_EHelper(lui) {
  rtl_sr(id_dest->reg, &id_src->val, 4);

  print_asm_template2(lui);
}

make_EHelper(auipc) {
printf("%x\n",*(&(cpu.pc)));  
  rtl_addi(id_dest->reg, &(cpu.pc) ,id_src->simm);

  print_asm_template2(auipc);
}

make_EHelper(addi){
  rtl_addi(id_dest, &id_src->val, id_src2->simm);
  print_asm_template2(addi);
}