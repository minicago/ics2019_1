#include "klib.h"
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)


static char NUM_CHAR[] = "0123456789ABCDEF";
int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
    int len = 0;
    char buf[128];
    int buf_len = 0;
    while(*fmt != '\0' && len < n){
        char* s; char c; int val;uint32_t uval,address;
        switch(*fmt) {
            case '%':
              fmt++;
              switch(*fmt) {
                case 'd':
                  val = va_arg(ap, int);    
                  if(val == 0) out[len++] = '0';
                  if(val < 0) {
                    out[len++] = '-';
                    val = 0 - val;
                  }
                  for(buf_len = 0; val; val /= 10, buf_len++)
                    buf[buf_len] = NUM_CHAR[val % 10];    
                  for(int i = buf_len - 1; i >= 0; i--)
                    out[len++] = buf[i];
                break;
                case 'u':
                  uval = va_arg(ap, uint32_t);
                break;
                case 'c':
                  c = (char)va_arg(ap, int);
                  out[len++] = c;
                break;
                case 's':
                  s = va_arg(ap, char*);
                  for(int i = 0; s[i] != '\0'; i++)
                    out[len++] = s[i];
                break;
                case 'p':
                  out[len++] = '0'; out[len++] = 'x';
                  address = va_arg(ap, uint32_t);
                  for(buf_len = 0; address; address /= 16, buf_len++)
                    buf[buf_len] = NUM_CHAR[address % 16];
                  for(int i = buf_len - 1; i >= 0; i--)
                    out[len++] = buf[i];
                break;               
              }
            break; 
            case '\n':
              out[len++] = '\n';
            break;
            default:
              out[len++] = *fmt;
        }
        fmt++;
    }
    out[len] = '\0';    
    return len;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  return vsnprintf(out, -1, fmt, ap);
}


int printf(const char *fmt, ...) {
  char buffer[1024];
  va_list arg;
  va_start(arg, fmt);

  int done = vsprintf(buffer, fmt, arg);
  for(int i=0; i<=5; i++){
    _putc(buffer[i]);
  }
  
  
  va_end(arg);
  return done;
}



int sprintf(char *out, const char *fmt, ...) {
  va_list arg;
  va_start(arg, fmt);

  int res = vsprintf(out,fmt, arg);

  va_end(arg);
  return res;
}


int snprintf(char *out, size_t n, const char *fmt, ...) {
  va_list arg;
  va_start(arg, fmt);

  int res = vsnprintf(out, n ,fmt, arg);

  va_end(arg);
  return res;
}

#endif
