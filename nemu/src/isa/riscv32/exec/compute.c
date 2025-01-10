#include "cpu/exec.h"

make_EHelper(lui) {
  rtl_sr(id_dest->reg, &id_src->val, 4);
  print_asm_template2(lui);
}

make_EHelper(auipc) {
  rtl_addi(&reg_l(id_dest->reg), pc , id_src->simm);
  print_asm_template2(auipc);
}

// #define make_ISAEHelper(name) \
//   make_EHelper(name){ \
//     concat(rtl_, name)(&reg_l(id_dest->reg), &id_src->val, id_src2->simm);\
//     print_asm_template3(name); \
//   }

// #define make_IUAEHelper(name) \
//   make_EHelper(name){ \
//     concat(rtl_, name)(&reg_l(id_dest->reg), &id_src->val, id_src2->imm);\
//     print_asm_template3(name); \
//   }


#define I_args &reg_l(id_dest->reg), &id_src->val, id_src2->val



make_EHelper(addi){
  // Log("%d+%d", id_src->val ,id_src2->val);
  SEXT(id_src2, 12);
  // Log("%d+%d", id_src->val ,id_src2->val);
  rtl_addi(I_args);
  print_asm_template3(addi);
}
make_EHelper(slti){
  SEXT(id_src2, 12);
  rtl_slti(I_args);
  print_asm_template3(slti);
}
make_EHelper(sltiu){ 
  rtl_sltui (I_args);
  print_asm_template3(sltiu); 
}
make_EHelper(xori){
  SEXT(id_src2, 12);
  rtl_xori(I_args);
  print_asm_template3(xori);
}
make_EHelper(ori){
  SEXT(id_src2, 12);
  rtl_ori(I_args);
  print_asm_template3(ori);  
}
make_EHelper(andi){
  // Log("%x&%x", id_src->val ,id_src2->val);
  SEXT(id_src2, 12);
  rtl_andi(I_args);
  print_asm_template3(andi); 
}
make_EHelper(shli){
  // Log("%d<<%d", id_src->val ,id_src2->val);
  rtl_shli (&reg_l(id_dest->reg), &id_src->val, id_src2->imm);
  print_asm_template3(slli);
}



make_EHelper(shri){
  switch (decinfo.isa.instr.funct7 )
  {
  case 0:
    rtl_shri(&reg_l(id_dest->reg), &id_src->val, id_src2->imm);
    print_asm_template3(srli); 
    break;
  
  case 0x20:
    rtl_sari(&reg_l(id_dest->reg), &id_src->val, id_src2->imm);
    print_asm_template3(srai);    
    break;
  }
}

#define R_arg &reg_l(id_dest->reg),&id_src->val, &id_src2->val

make_EHelper(add){
  // printf("%d %d %d \n",decinfo.isa.instr.funct7, id_src->val, id_src2->val);
  switch (decinfo.isa.instr.funct7 )
  {
  case 0:
    rtl_add(R_arg);
    print_asm_template3(add);
    break;

  case 0x20:
    rtl_sub(R_arg);
    print_asm_template3(sub);
    break;
  }
}

make_EHelper(shl){
  rtl_shl(R_arg);
  print_asm_template3(sll);
}

make_EHelper(slt){
  rtl_slt(R_arg);
  // Log("%d<%d %d", id_src->val ,id_src2->val, c_slt(id_src->val, id_src2->val));
  
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
  switch (decinfo.isa.instr.funct7 ){
  case 0: 
    rtl_shr(R_arg);
    print_asm_template3(srl);
    break;
  case 20 :
    rtl_sar(R_arg);
    print_asm_template3(sra);
    break;
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


