#include "cpu/exec.h"

make_EHelper(lui) {
  rtl_sr(id_dest->reg, &id_src->val, 4);
  print_asm_template2(lui);
}

make_EHelper(auipc) {
  rtl_addi(&reg_l(id_dest->reg), pc , id_src->simm);
  print_asm_template2(auipc);
}

#define make_ISAEHelper(name) \
  make_EHelper(name){ \
    concat(rtl_, name)(&reg_l(id_dest->reg), &reg_l(id_src->reg), id_src2->simm);\
    print_asm_template3(name); \
  }

#define make_IUAEHelper(name) \
  make_EHelper(name){ \
    concat(rtl_, name)(&reg_l(id_dest->reg), &reg_l(id_src->reg), (0x7ff) & id_src2->imm);\
    print_asm_template3(name); \
  }

make_ISAEHelper(addi)
make_ISAEHelper(slti)
make_EHelper(sltiu){ 
  rtl_sltui (&reg_l(id_dest->reg), &id_src->val, id_src2->imm);
  print_asm_template3(sltiu); 
}
make_IUAEHelper(xori)
make_IUAEHelper(ori)
make_IUAEHelper(andi)
make_EHelper(shli){
  printf("%x\n",reg_l(id_dest->reg));
  printf("%x\n",id_src->val);


  rtl_shl (&reg_l(id_dest->reg), &id_src->val, id_src2->imm);
  printf("ok!\n");
  print_asm_template3(slli);
}


#define TYPE1 if(decinfo.isa.instr.funct7 & (1 << 5))
#define TYPE2 if(!(decinfo.isa.instr.funct7 & (1 << 5)))

make_EHelper(shri){
  TYPE1 {
    rtl_sari(&reg_l(id_dest->reg), &id_src->val, id_src2->imm);
    print_asm_template3(srai);
  } 

  TYPE2 {
    rtl_shri(&reg_l(id_dest->reg), &id_src->val, id_src2->imm);
    print_asm_template3(srli);
  }
}

#define R_arg &reg_l(id_dest->reg),&id_src->val, &id_src2->val

make_EHelper(add){
  TYPE1 {
    rtl_add(R_arg);
    print_asm_template3(add);
  }
  TYPE2 {
    rtl_sub(R_arg);
    print_asm_template3(sub);
  }
}

make_EHelper(shl){
  rtl_shl(R_arg);
  print_asm_template3(sll);
}

make_EHelper(slt){
  rtl_slt(R_arg);
  print_asm_template3(slt);
}

make_EHelper(sltu){
  rtl_sltu(R_arg);
  print_asm_template3(sltu);  
}

make_EHelper(xor){
  rtl_xor(R_arg);
  print_asm_template3(xor);
}

make_EHelper(shr){
  TYPE1 {
    rtl_sar(R_arg);
    print_asm_template3(sra);
  } 

  TYPE2 {
    rtl_shr(R_arg);
    print_asm_template3(srl);
  }
}

make_EHelper(or){
  rtl_or(R_arg);
  print_asm_template3(or);
}

make_EHelper(and){
  rtl_and(R_arg);
  print_asm_template3(and);
}


