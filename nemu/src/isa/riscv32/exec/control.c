#include "cpu/exec.h"
make_EHelper(jal){
  rtl_addi(&reg_l(id_dest->reg), pc , 4);
  print_asm_template2(jal);
  // printf("to:%x",id_src->imm);
  rtl_j(id_src->imm);
  // *pc = *pc + id_src->simm + 4;
}

make_EHelper(jalr){
  // printf("ok");
  //  printf("%x %x %x\n", *pc, reg_l(id_src->reg), id_src2->simm);
  
  rtl_addi(&t0, &reg_l(id_src->reg), id_src2->simm);
  rtl_andi(&t0,&t0,~1);
  rtl_addi(&reg_l(id_dest->reg), pc , 4);
  print_asm_template3(jalr);
//  printf("to:%x",t0);
  rtl_j(t0);
}

uint32_t relop_table[] = {
  RELOP_EQ, RELOP_NE, RELOP_FALSE, RELOP_FALSE, RELOP_LT, RELOP_GE, RELOP_LTU, RELOP_GEU
};

make_EHelper(B){
  rtl_addi(&t0, pc, id_dest->simm);
  rtl_jrelop(relop_table[decinfo.isa.instr.funct3], &id_src->val, &id_src2->val, t0);
}
