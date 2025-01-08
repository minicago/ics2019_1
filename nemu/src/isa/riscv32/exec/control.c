#include "cpu/exec.h"
make_EHelper(jal){
    // printf("jal %x\n",*pc + id_src->simm + 4);
  rtl_li(id_dest, *pc + id_src->simm + 4);
  *pc = *pc + id_src->simm + 4;
}

make_EHelper(ret){
    *pc = (vaddr_t) reg_l(1);
}