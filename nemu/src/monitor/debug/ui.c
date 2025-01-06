#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void cpu_exec(uint64_t);

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}

static int cmd_q(char *args) {
  return -1;
}

static int cmd_si(char *args){
  int step = 1;
  if(args != NULL && strcmp(args,"") != 0){
    if (sscanf(args,"%d",&step) != 1){
      printf("illegal format!\n");
      return 0;
    }
  }
  cpu_exec(step);
  return 0;
}

static int cmd_info(char* args){
  if (args == NULL) {
    printf("wrong subcommand!\n");
  }
  else if (strcmp(args,"r") == 0){
    isa_reg_display();
  } else if (strcmp(args,"w") == 0){
    list_wp();
  } else {
    printf("wrong subcommand!\n");
  }

  return 0;
}

static int cmd_p(char* args){
  bool success = false;
  uint32_t old_value = expr(args, &success);
  if(!success){
    printf("bad expr!");
    return 0;
  } else {
    printf("0x%x\n",old_value);
  }  
  return 0;
}

static int cmd_x(char* args){
  bool success;
  int n;
  char buf[256];
  sscanf(args, "%d %s",&n, buf);
  uint32_t ptr = expr(buf, &success);
  for(int i = 0; i < n; i++){
    printf("0x%x\n",vaddr_read(ptr + 4 * i, 4));
  }
  return 0;
}

static int cmd_w(char* args){
  bool success = false;
  uint32_t old_value = expr(args, &success);
  if(!success){
    printf("bad expr!");
    return 0;
  }
  WP* wp = new_wp();
  strcpy(wp->str, args);
  wp->old_value = old_value;
  list_wp();
  return 0;
}

static int cmd_d(char* args){
  int x;
  if(args == NULL || sscanf("%d",&x) != 1){
    return 0;
  }
  free_wp(wp_NO(x));
  return 0;
}

static int cmd_help(char *args);

static struct {
  char *name;
  char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display informations about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },
  { "si", "run N instructions", cmd_si},
  { "info", "print program state", cmd_info },
  { "p", "calculate expression", cmd_p },
  { "x", "scan memory", cmd_x },
  { "w", "add watch point", cmd_w},
  { "d", "delete watch point", cmd_d},

  /* TODO: Add more commands */

};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

void ui_mainloop(int is_batch_mode) {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef HAS_IOE
    extern void sdl_clear_event_queue(void);
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}
