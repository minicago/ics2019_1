#include "common.h"
#include "syscall.h"

void sys_exit(int status){
  _halt(status);
}

void sys_yield(){
  _yield();
}

uint32_t sys_write(int fd, void* buf, size_t count) {
  for(int i=0 ;i<count; i++){
    _putc(*(((char*)buf) +i));
  }
  return 0;
}

uint32_t sys_sbrk(intptr_t new_brk) {
  return 0;
}

_Context* do_syscall(_Context *c) {
  uintptr_t a[4];
  a[0] = c->GPR1;
  Log("%d",a[0]);

  switch (a[0]) {
    case SYS_exit:
        sys_exit(c->GPR2);
        break;
    case SYS_yield:
        sys_yield();
        break;
    case SYS_write : 
        c->GPRx = sys_write(c->GPR2, (void*)c->GPR3, c->GPR4);
        break;
    case SYS_brk :
        c->GPRx = sys_sbrk((intptr_t)c->GPR2);
        // printf("ok!");
        break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }

  return NULL;
}
