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
  _DEV_INPUT_KBD_t *kbd = (_DEV_INPUT_KBD_t *)buf;
  int k = _KEY_NONE;

  // SDL_LockMutex(key_queue_lock);
  if (key_f != key_r) {
    k = key_queue[key_f];
    key_f = (key_f + 1) % KEY_QUEUE_LEN;
  }
  // SDL_UnlockMutex(key_queue_lock);

  kbd->keydown = (k & KEYDOWN_MASK ? 1 : 0);
  kbd->keycode = k & ~KEYDOWN_MASK;

  return sizeof(_DEV_INPUT_KBD_t);
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
