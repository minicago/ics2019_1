#include "nemu.h"
#include "macro.h"

const char *regsl[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

void isa_reg_display() {
  for(int i = 0; i < sizeof(regsl) / sizeof(regsl[0]); i++){
    printf("%-4s: 0x%08x\n", regsl[i], cpu.gpr[i]._32);
  }
}

uint32_t isa_reg_str2val(const char *s, bool *success) {
  *success = false;
  // printf("reg:%s\n",s);
  if (strcmp(s,"0") == 0) {
    *success = true;
    return cpu.gpr[0]._32;
  }
  for(int i = 0; i < sizeof(regsl) / sizeof(regsl[0]); i++){
    if(strcmp(s,regsl[i])==0){
      *success = true;
      return cpu.gpr[i]._32;
    }
  }
  return 0;
}

#define CSR_info(name, index) {&cpu.name, index}

const CSR_info CSR_table[]={
  CSR_info(stvec, 0x105), CSR_info(sepc, 0x141), CSR_info(sstatus, 0x100), CSR_info(scause, 0x142),
};

rtlreg_t *CSR(uint32_t CSR_index){
  for(int i = 0; i < sizeof(CSR_table) / sizeof(CSR_info); i++ ){
    if(CSR_index == CSR_table[i].index) return CSR_table[i].value;
  }
  return NULL;
}