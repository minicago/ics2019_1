#include "common.h"
#include <amdev.h>

#include <am.h>
#include <fs.h>
// #include <ndl.h>

#define KEYDOWN_MASK 0x8000

#define KEY_QUEUE_LEN 1024
static int key_queue[KEY_QUEUE_LEN] = {};
static int key_f = 0, key_r = 0;
// static SDL_mutex *key_queue_lock = NULL;

size_t serial_write(const void *buf, size_t offset, size_t len) {
  char *cbuf = (char *)buf;
  // Log("%x", cbuf);
  for (int i = 0; i < len; i++) {
    _putc(cbuf[i]);
  }
  return len;

}

#define NAME(key) \
  [_KEY_##key] = #key,

static const char *keyname[256] __attribute__((used)) = {
  [_KEY_NONE] = "NONE",
  _KEYS(NAME)
};

size_t events_read(void *buf, size_t offset, size_t len) {
  int key=read_key();
  int flag=0;
  if(key&0x8000){
    key^=0x8000;
    flag=1;
  }
  if(key!=_KEY_NONE){
    if(flag)
      len=sprintf(buf,"kd %s\n",keyname[key]);
    else
      len=sprintf(buf,"ku %s\n",keyname[key]);
  }
  else{
    len=sprintf(buf,"t %u\n",uptime());
  }
  return len;
}

static char dispinfo[128] __attribute__((used)) = {};

size_t dispinfo_read(void *buf, size_t offset, size_t len) {
  strncpy(buf, dispinfo + offset, len);
  return strlen(buf);
}

size_t fb_write(const void *buf, size_t offset, size_t len) {
  offset /= 4;
  len /= 4;
  uint32_t* pixels = (uint32_t *)buf;
  uint32_t x = offset % screen_width();
  uint32_t y = offset / screen_width();
  uint32_t w = len, h = 1;
  Log("%d %d %d %d", x, y, w, h);
  draw_rect(pixels, x, y, w, h);
  return 0;
}

size_t fbsync_write(const void *buf, size_t offset, size_t len) {
  draw_sync();  
  return 0;
}

void fb_init();
// int fs_open(const char *pathname, int flags, int mode);
void init_device() {
  Log("Initializing devices...");
  _ioe_init();
  sprintf((char *)dispinfo, "WIDTH:%d\nHEIGHT:%d\n", screen_width(), screen_height());
  
  // TODO: print the string to array `dispinfo` with the format
  // described in the Navy-apps convention
}
