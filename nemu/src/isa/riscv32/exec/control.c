#include "cpu/exec.h"
static make_EHelper(jal){
  rtl_li(id_dest, id_src->simm + 4);
  pc = id_src->simm + 4;
}