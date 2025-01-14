#include "common.h"
#include <amdev.h>

#include <am.h>

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
  _DEV_INPUT_KBD_t key;
  _io_read(_DEV_INPUT, _DEVREG_INPUT_KBD, &key, len);
  int ret = 0;
  if (key.keycode == _KEY_NONE) {
    *(char *)buf = '\0';
  } else {
    ret = sprintf((char *)buf, "%s %s\n\0", key.keydown ? "kd" : "ku", keyname[key.keycode]);
  }
  return ret;
}

static char dispinfo[128] __attribute__((used)) = {};

size_t dispinfo_read(void *buf, size_t offset, size_t len) {
  return 0;
}

size_t fb_write(const void *buf, size_t offset, size_t len) {
  return 0;
}

size_t fbsync_write(const void *buf, size_t offset, size_t len) {
  return 0;
}

void init_device() {
  Log("Initializing devices...");
  _ioe_init();

  // TODO: print the string to array `dispinfo` with the format
  // described in the Navy-apps convention
}
