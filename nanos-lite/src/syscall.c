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
  return count;
}

uint32_t sys_sbrk(intptr_t new_brk) {
  return 0;
}

_Context* do_syscall(_Context *c) {
  uintptr_t a[4];
  a[0] = c->GPR1;
  a[1] = c->GPR2;
  a[2] = c->GPR3;
  a[3] = c->GPR4;
  // Log("%d %d %d %d",a[0], a[1], a[2], a[3]);

  switch (a[0]) {
    case SYS_exit:
        sys_exit(a[1]);
        break;
    case SYS_yield:
        sys_yield();
        break;
    case SYS_write : 
        c->GPRx = fs_write(a[1], (char *)a[2], a[3]);
        break;
    case SYS_open :
        c->GPRx = fs_open((char *)a[1], a[2], a[3]);
        break;
    case SYS_read :
        c->GPRx = fs_read(a[1], (char *)a[2], a[3]);
        break;
    case SYS_lseek :
        c->GPRx = fs_lseek(a[1], a[2], a[3]);
        break;
    case SYS_close :
        c->GPRx = fs_close(a[1]);
        break;
    case SYS_brk :
        c->GPRx = sys_sbrk((intptr_t)a[1]);
        break;
    case SYS_execve :
        naive_uload(NULL, (char*)a[1]);
        break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }

  return NULL;
}
