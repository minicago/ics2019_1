#include "cpu/exec.h"
#include "all-instr.h"

static OpcodeEntry load_table [8] = {
  EXW(sld, 1), EXW(sld, 2), EXW(ld, 4), EXW(ld, 1), EXW(ld, 2), EMPTY, EMPTY, EMPTY
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
  EXW(addi, 4), IDEX(shamt, shli), EXW(slti, 4), EXW(sltiu, 4), EXW(xori, 4),IDEX(shamt, shri), EXW(ori, 4), EXW(andi,4),  
};

static make_EHelper(compute_i) {
  decinfo.width = compute_i_table[decinfo.isa.instr.funct3].width;
  idex(pc, &compute_i_table[decinfo.isa.instr.funct3]);  
}

static OpcodeEntry compute_r_table [8] = {
  EXW(add, 4),EXW(shl, 4), EXW(slt, 4), EXW(sltu, 4), EXW(xor, 4),EXW(shr, 4), EXW(or, 4), EXW(and,4),  
};

static make_EHelper(compute_r) {
  decinfo.width = compute_r_table[decinfo.isa.instr.funct3].width;
  idex(pc, &compute_r_table[decinfo.isa.instr.funct3]);  
}

static OpcodeEntry opcode_table [32] = {
  /* b00 */ IDEX(ld, load), EMPTY, EMPTY, EMPTY, IDEX(I,compute_i), IDEX(U, auipc), EMPTY, EMPTY,
  /* b01 */ IDEX(st, store), EMPTY, EMPTY, EMPTY, IDEX(R,compute_r), IDEX(U, lui), EMPTY, EMPTY,
  /* b10 */ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
  /* b11 */ EMPTY, IDEX(I, jalr), EX(nemu_trap), IDEX(J, jal), EMPTY, EMPTY, EMPTY, EMPTY,
};
void isa_exec(vaddr_t *pc) {
  decinfo.isa.instr.val = instr_fetch(pc, 4);
  assert(decinfo.isa.instr.opcode1_0 == 0x3);
  // printf("id: %x\n",decinfo.isa.instr.opcode6_2);
  idex(pc, &opcode_table[decinfo.isa.instr.opcode6_2]);
}
