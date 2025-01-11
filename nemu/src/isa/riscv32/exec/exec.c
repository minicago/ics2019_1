#include "cpu/exec.h"
#include "all-instr.h"

static OpcodeEntry load_table [8] = {
  EXW(sld, 1), EXW(sld, 2), EXW(ld, 4), EMPTY, EXW(ld, 1), EXW(ld, 2), EMPTY, EMPTY
};

static make_EHelper(load) {
  decinfo.width = load_table[decinfo.isa.instr.funct3].width;
  idex(pc, &load_table[decinfo.isa.instr.funct3]);
}

static OpcodeEntry store_table [8] = {
  EXW(st, 1), EXW(st, 2), EXW(st, 4), EMPTY, EMPTY, EMPTY, EMPTY, EMPTY
};

static make_EHelper(store) {
  decinfo.width = store_table[decinfo.isa.instr.funct3].width;
  idex(pc, &store_table[decinfo.isa.instr.funct3]);
}

static OpcodeEntry compute_i_table [8] = {
  EX(addi), IDEX(shamt, shli), EX(slti), EX(sltiu), EX(xori),IDEX(shamt, shri), EX(ori), EX(andi),  
};

static make_EHelper(compute_i) {
  idex(pc, &compute_i_table[decinfo.isa.instr.funct3]);  
}

static OpcodeEntry compute_r_table [8] = {
  EX(add),EX(shl), EX(slt), EX(sltu), EX(xor),EX(shr), EX(or), EX(and),  
};

static OpcodeEntry mul_table [8] = {
  EX(mul),EX(mulh), EX(mulhsu), EX(mulhu), EX(div), EX(divu), EX(rem), EX(remu),  
};

static make_EHelper(compute_r) {
  if (decinfo.isa.instr.funct7 == 1){
    idex(pc, &mul_table[decinfo.isa.instr.funct3]);
  }
  else idex(pc, &compute_r_table[decinfo.isa.instr.funct3]);  
}

static OpcodeEntry csr_table [8] = {
  EX(ecall), IDEX(CSRR, CSRRW), IDEX(CSRR, CSRRS), IDEX(CSRR, CSRRC), EMPTY, IDEX(CSRI, CSRRW), IDEX(CSRI, CSRRS), IDEX(CSRI, CSRRC),
};

static make_EHelper(CSR){
  idex(pc, &csr_table[decinfo.isa.instr.funct3]);
}

static OpcodeEntry opcode_table [32] = {
  /* b00 */ IDEX(ld, load), EMPTY, EMPTY, EMPTY, IDEX(I,compute_i), IDEX(U, auipc), EMPTY, EMPTY,
  /* b01 */ IDEX(st, store), EMPTY, EMPTY, EMPTY, IDEX(R,compute_r), IDEX(U, lui), EMPTY, EMPTY,
  /* b10 */ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
  /* b11 */ IDEX(B, B), IDEX(I, jalr), EX(nemu_trap), IDEX(J, jal), IDEX(CSR, CSR), EMPTY, EMPTY, EMPTY,
};
void isa_exec(vaddr_t *pc) {
  decinfo.isa.instr.val = instr_fetch(&decinfo.seq_pc, 4);
  // if(*pc==0x80100080) {
  //   printf("add %x %x\n", reg_l(10), reg_l(18));
  // }
  // printf("0x%x %x\n",*pc, decinfo.isa.instr.val);

  assert(decinfo.isa.instr.opcode1_0 == 0x3);
  // printf("id: %x\n",decinfo.isa.instr.opcode6_2);
  

  idex(pc, &opcode_table[decinfo.isa.instr.opcode6_2]);
  // printf("a0=%x a1=%x a5=%x\n", reg_l(10), reg_l(11), reg_l(15));
  

  
  
}
