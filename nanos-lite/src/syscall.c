#include "common.h"
#include "syscall.h"

void sys_exit(_Context *c){
  uintptr_t a[4];
  a[0] = c->GPR1;
  a[1] = c->GPR2;
  _halt(a[1]);
}

void sys_yield(_Context *c){
  _yield();
}

_Context* do_syscall(_Context *c) {
  uintptr_t a[4];
  a[0] = c->GPR1;
  // Log("%d %d %d",a[0],SYS_exit, SYS_yield);

  switch (a[0]) {
    case SYS_exit:
        sys_exit(c);
        break;
    case SYS_yield:
        sys_yield(c);
        break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }

  return NULL;
}
