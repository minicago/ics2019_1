#include <stdint.h>

#define SYS_yield 1
extern int _syscall_(int, uintptr_t, uintptr_t, uintptr_t);

int main() {
  int a1=0;
  printf("%d\n",a1);
  return _syscall_(SYS_yield, a1, 0, 0);
}
