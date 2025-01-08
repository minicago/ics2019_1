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
make_ISAEHelper(slti)
make_EHelper(sltiu){ 
  rtl_slti (&reg_l(id_dest->reg), &id_src->val, id_src2->imm);
  print_asm_template2(sltiu); 
}
make_IUAEHelper(xori)
make_IUAEHelper(ori)
make_IUAEHelper(andi)
make_IUAEHelper(slli)
make_IUAEHelper(srli)
make_IUAEHelper(srai)


