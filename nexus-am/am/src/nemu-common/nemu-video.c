#include <am.h>
#include <amdev.h>
#include <nemu.h>

size_t __am_video_read(uintptr_t reg, void *buf, size_t size) {
  switch (reg) {
    case _DEVREG_VIDEO_INFO: {
      _DEV_VIDEO_INFO_t *info = (_DEV_VIDEO_INFO_t *)buf;
      info->width = ((uint32_t) inl(SCREEN_ADDR)) >> 16;
      info->height = inl(SCREEN_ADDR) & 0xffff;
      return sizeof(_DEV_VIDEO_INFO_t);
    }
  }
  return 0;
}

size_t __am_video_write(uintptr_t reg, void *buf, size_t size) {
  switch (reg) {
    case _DEVREG_VIDEO_FBCTL: {
      _DEV_VIDEO_FBCTL_t *ctl = (_DEV_VIDEO_FBCTL_t *)buf;
        int x = ctl->x, y = ctl->y, w = ctl->w, h = ctl->h;
        if (!ctl->sync && (w == 0 || h == 0))
          return;
        uint32_t *pixels = ctl->pixels;
        uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
        uint32_t screen_w = inl(SCREEN_ADDR) >> 16;
        for (int i = y; i < y+h; i++) {
          for (int j = x; j < x+w; j++) {
            fb[screen_w*i+j] = pixels[w*(i-y)+(j-x)]; 
          }
        }

      if (ctl->sync) {
        outl(SYNC_ADDR, 0);
      }
      return size;
    }
  }
  return 0;
}

void __am_vga_init() {
  // printf("%x %x\n",screen_width(), screen_height());
  int i;
  int size = screen_width() * screen_height();
  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  for (i = 0; i < size; i ++) fb[i] = i;
  draw_sync();
}
