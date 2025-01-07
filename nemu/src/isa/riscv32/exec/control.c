#include "cpu/exec.h"
make_EHelper(jal){
  rtl_li(id_dest, *pc + id_src->simm + 4);
  pc = *pc + id_src->simm + 4;
}