#ifndef __TRAP_H__
#define __TRAP_H__

#include <am.h>
#include <klib.h>
#include <stdio.h>

__attribute__((noinline))
void nemu_assert_(int cond) {

  if (!cond) {
    _halt(1);
  }
}

#define nemu_assert(cond) do{ \
  printf(#cond); \
  nemu_assert_(cond); \
  } while (0)
  
  

#endif
