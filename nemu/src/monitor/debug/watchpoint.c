#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = &wp_pool[i + 1];
  }
  wp_pool[NR_WP - 1].next = NULL;

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

WP* new_wp(){
  WP* tmp = free_;
  free_ = tmp->next;
  tmp->next = head;
  head = tmp;
  return tmp;
}

WP* wp_NO(int NO){
  return wp_pool + NO;
}

void free_wp(WP *wp){
  bool success = false;
  if(head == wp){
    head = wp->next;
    success = true;
  }
  else{
    
    for(WP* p = head; p->next != NULL; p = p->next){
      if(p->next == wp){
        p->next=p->next->next;
        success = true;
        break;
      }
    }
  }
 if(success){
  wp->next = free_;
  free_ = wp;    
 }
  
}

bool watch_wp(){
  bool success = true;
  bool flag = false;
  for(WP* wp = head; wp != NULL; wp = wp->next){
    int num = expr(wp->str, &success);
    if(wp->old_value != num){
      printf("watch point NO.%d: %s : (0x%x -> 0x%x)\n", wp->NO, wp->str, wp->old_value, num);
      flag = true;
    }
  }
  return flag;
}

void list_wp(){
  for(WP* wp = head; wp != NULL; wp = wp->next){
    printf("watch point NO.%d: %s : (0x%x)\n", wp->NO, wp->str, wp->old_value);
  }
}
