#include "cpu/exec.h"
make_EHelper(jal){
    // printf("jal %x\n",*pc + id_src->simm + 4);
  rtl_addi(&reg_l(id_dest->reg), pc , 4);
  rtl_j(id_src->simm);
  // *pc = *pc + id_src->simm + 4;
}

make_EHelper(ret){
  rtl_jr(reg_l(1));
}