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
  rtl_sltiu (&reg_l(id_dest->reg), &id_src->val, id_src2->imm);
  print_asm_template2(sltiu); 
}
make_IUAEHelper(xori)
make_IUAEHelper(ori)
make_IUAEHelper(andi)
make_EHelper(shli){
  rtl_shl (&reg_l(id_dest->reg), &id_src->val, id_src2->imm);
  print_asm_template2(slli);
}

#define shamt(x) (x & 0x1f)
#define TYPE1 if(decinfo.isa.instr.funct7 & (1 << 5))
#define TYPE2 if(!(decinfo.isa.instr.funct7 & (1 << 5)))

make_EHelper(shri){
  TYPE1 {
    rtl_sari(&reg_l(id_dest->reg), &id_src->val, shamt(id_src2->imm));
    print_asm_template2(srai);
  } 

  TYPE2 {
    rtl_shri(&reg_l(id_dest->reg), &id_src->val, shamt(id_src2->imm));
    print_asm_template2(srli);
  }
}
#define R_arg &reg_l(id_dest->reg),&id_src->val, &id_src2->val

make_EHelper(add){
  TYPE1 {
    rtl_add(R_arg);
  }
  TYPE2 {
    rtl_sub(R_arg);
  }
    
}

make_EHelper(sll){
  rtl_shl(R_arg);
}

make_EHelper(slt){
  rtl_shl(R_arg);
}


