#include "cpu/exec.h"
make_EHelper(jal){
    // printf("jal %x\n",*pc + id_src->simm + 4);
  rtl_addi(&reg_l(id_dest->reg), pc , 4);
  rtl_addi(&t0, pc, id_src->simm);
  printf("%x\n",t0);
  rtl_j(t0);
  // *pc = *pc + id_src->simm + 4;
}

make_EHelper(jalr){
  printf("ok");
  rtl_addi(&reg_l(id_dest->reg), pc , 4);
  rtl_addi(&t0, &reg_l(id_src->reg), id_src2->simm);
  rtl_jr(t0);
}