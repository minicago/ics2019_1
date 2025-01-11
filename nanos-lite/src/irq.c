#include "common.h"

static _Context* do_event(_Event e, _Context* c) {
  _Context* next = c;
  switch (e.event) {
    case _EVENT_YIELD:
      printf("YIELD!");
      break;

    case _EVENT_SYSCALL:
      do_syscall(c);
      break;
    default: panic("Unhandled event ID = %d", e.event);
  }
  return next;
}

void init_irq(void) {
  Log("Initializing interrupt/exception handler...");
  _cte_init(do_event);
}
