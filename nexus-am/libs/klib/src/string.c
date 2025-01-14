#include "klib.h"

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  for(int i = 0; ; i++){
    if(s[i]==0) return i;
  }
  return 0;
}

char *strcpy(char* dst,const char* src) {
  for(int i = 0; ; i++){
    dst[i] = src[i];
    if(src[i] == 0) break;
  }
  return dst;
}

char* strncpy(char* dst, const char* src, size_t n) {
  for(int i = 0; i < n; i++){
    dst[i] = src[i];
    if(src[i] == 0) break;
  }
  return dst;
}

char* strcat(char* dst, const char* src) {
  int dst_len = strlen(dst);
  for(int i = 0; ; i++){
    dst[dst_len + i] = src[i];
    if(src[i] == 0) break;
  }
  return dst;
}

int strcmp(const char* s1, const char* s2) {
  for (int i = 0; ; i++){
    if(s1[i]==0 && s2[i]==0) return 0;
    else if(s1[i] < s2[i]) return -1;
    else if(s1[i] > s2[i]) return 1;
  }
  return 0;
}

int strncmp(const char* s1, const char* s2, size_t n) {
  for (int i = 0; i < n ; i++){
    if(s1[i]==0 && s2[i]==0) return 0;
    else if(s1[i] != s2[i]) return -1;
  }
  return 0;
}

void* memset(void* v,int c,size_t n) {
  for(int i=0; i<n; i++){
    *(char*)(v+i) = c;
  }
  return v;
}

void* memcpy(void* out, const void* in, size_t n) {
  for(int i=0; i<n; i++){
    *(char*)(out+i) = *(char*)(in+i);
  }
  return out;
}

int memcmp(const void* s1, const void* s2, size_t n){
  for (int i = 0; i < n ; i++){
    if(*(char*) (s1+i) !=*(char*) (s2+i) ) return -1;
  }  
  return 0;
}

#endif
