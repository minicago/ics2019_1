#include "rtl/rtl.h"

void raise_intr(uint32_t NO, vaddr_t epc) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * That is, use ``NO'' to index the IDT.
   */
    cpu.sepc = epc;
    cpu.scause = NO;
    // cpu.sstatus = 0;
    // for(int i=0; i<32; i++){
    //   printf("%d %x\n",i, cpu.gpr[i]._32);
    // }    
    rtl_jr(&cpu.stvec);  
}

bool isa_query_intr(void) {
  return false;
}
