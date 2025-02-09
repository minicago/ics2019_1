#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum {
  TK_NOTYPE = 256, 
  TK_EQ, 
  TK_NEQ, 
  TK_REG, 
  TK_HEX, 
  TK_DEC, 
  TK_AND,
  TK_PTR,

  /* TODO: Add more token types */

};

static struct rule {
  char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +", TK_NOTYPE},    // spaces
  {"\\+", '+'},         // plus
  {"==", TK_EQ},         // equal
  {"\\-", '-'},
  {"/", '/'},
  {"\\*", '*'},
  {"!=", TK_NEQ},
  {"\\(",'('},
  {"\\)",')'},
  {"0[xX][0-9a-fA-F]+",TK_HEX},
  {"\\$[0-9a-z]+", TK_REG},
  {"[0-9]+",TK_DEC},
  
  {"&&", TK_AND},

};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);
        

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
          case TK_NOTYPE :
            break;
          
          case '*':
            if (nr_token == 0 || 
            (tokens[nr_token-1].type != ')' 
            && tokens[nr_token-1].type != TK_DEC
            && tokens[nr_token-1].type != TK_HEX
            )
            ){
              tokens[nr_token].type = TK_PTR;

            }else {
              tokens[nr_token].type = rules[i].token_type;
            }
              strncpy(tokens[nr_token].str, e+position, substr_len);
              nr_token++;            
            break;

          default :
            tokens[nr_token].type = rules[i].token_type;
            strncpy(tokens[nr_token].str, e+position, substr_len);
            nr_token++;
            break;
        }
        position += substr_len;
        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}

static int32_t num_stack[32] __attribute__((used)) = {};
static int sign_stack[32] __attribute__((used)) = {};
static int num_stack_top __attribute__((used)) = 0;
static int sign_stack_top __attribute__((used)) = 0;

int priority_of_sign(int type){
  switch (type)
  {
  case '(':
    return 0;
    /* code */
  case TK_PTR:
    return 1;
  case '*':
  case '/':
    return 2;
  case '+':
  case '-':
    return 3;
  case TK_EQ:
  case TK_NEQ:
    return 4;
  case TK_AND:
    return 5;
  case ')':
    return 6;   
  
  default:
    return -1;
  }
}

int conduct_sign(int type){
  switch (type)
  {
  case '(':
    return 1;
    /* code */
  case TK_PTR:
    num_stack[num_stack_top - 1] = vaddr_read(num_stack[num_stack_top - 1], sizeof(uint32_t));
    break;  
  case '*':
    num_stack_top--;
    num_stack[num_stack_top - 1] = num_stack[num_stack_top - 1] * num_stack[num_stack_top];
    break;  
  case '/':
    num_stack_top--;
    num_stack[num_stack_top - 1] = num_stack[num_stack_top - 1] / num_stack[num_stack_top];
    break;  
  case '+':
    num_stack_top--;
    num_stack[num_stack_top - 1] = num_stack[num_stack_top - 1] + num_stack[num_stack_top];
    break;  
  case '-':
    num_stack_top--;
    num_stack[num_stack_top - 1] = num_stack[num_stack_top - 1] - num_stack[num_stack_top];
    break;  
  case TK_EQ:
    num_stack_top--;
    num_stack[num_stack_top - 1] = num_stack[num_stack_top - 1] == num_stack[num_stack_top];
    break;
  case TK_NEQ:
    num_stack_top--;
    num_stack[num_stack_top - 1] = num_stack[num_stack_top - 1] != num_stack[num_stack_top];
    break;
  case TK_AND:
    num_stack_top--;
    num_stack[num_stack_top - 1] = num_stack[num_stack_top - 1] && num_stack[num_stack_top];
    break;
  default:
    return 0;
  }
  return 0;
}

uint32_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }
  /* TODO: Insert codes to evaluate the expression. */
  *success = true;
  num_stack_top = 0;
  sign_stack_top = 0;
  for (int i = 0; i < nr_token; i++) {
    int num = 0;
    bool subsuccess = true;
    switch(tokens[i].type){
      case TK_DEC:
        sscanf(tokens[i].str,"%d",&num);
        num_stack[num_stack_top++] = num;
        break;
      case TK_HEX:
        sscanf(tokens[i].str,"0x%x",&num);
        num_stack[num_stack_top++] = num;
        break;
      case TK_REG: 
        num = isa_reg_str2val(tokens[i].str + 1, &subsuccess);
        num_stack[num_stack_top++] = num;
        break;

      default:
        while(sign_stack_top > 0 && priority_of_sign(tokens[i].type) > priority_of_sign(sign_stack[sign_stack_top - 1]) ){
          if(conduct_sign(sign_stack[--sign_stack_top])) break;
        }
        if(tokens[i].type != ')') sign_stack[sign_stack_top++] = tokens[i].type;
        break;
    }    
  }
  while(sign_stack_top > 0){
    conduct_sign(sign_stack[--sign_stack_top]);
  }
  return num_stack[0];
}
