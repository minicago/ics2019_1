#include "fs.h"

typedef size_t (*ReadFn) (void *buf, size_t offset, size_t len);
typedef size_t (*WriteFn) (const void *buf, size_t offset, size_t len);

typedef struct {
  char *name;
  size_t size;
  size_t disk_offset;
  size_t open_offset;
  ReadFn read;
  WriteFn write;

} Finfo;

enum {FD_STDIN, FD_STDOUT, FD_STDERR, FD_FB};

size_t invalid_read(void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

size_t invalid_write(const void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}
size_t serial_write(const void *buf, size_t offset, size_t len);
/* This is the information about all files in disk. */
static Finfo file_table[] __attribute__((used)) = {
  {"stdin", 0, 0, 0, invalid_read, invalid_write},
  {"stdout", 0, 0, 0, invalid_read, serial_write},
  {"stderr", 0, 0, 0, invalid_read, serial_write},
#include "files.h"
};

#define NR_FILES (sizeof(file_table) / sizeof(file_table[0]))

void init_fs() {
  // TODO: initialize the size of /dev/fb
}

int fs_open(const char *pathname, int flags, int mode) {
  int ft_len = sizeof(file_table) / sizeof(file_table[0]);
  for (int i = 3; i < ft_len; i++) {
    if (strcmp(pathname, file_table[i].name) == 0) {
      file_table[i].open_offset = 0;
      return i;
    }
  }
  return 0;
}

size_t fs_read(int fd, void *buf, size_t len) {
  if (file_table[fd].read) {
    return file_table[fd].read(buf, file_table[fd].open_offset , len);
  }
  
  size_t size = file_table[fd].size;
  size_t open_offset = file_table[fd].open_offset;
  
  int real_len = len;
  if (open_offset + len > size) {
    real_len = size - open_offset;
  }

  int ret = ramdisk_read(buf, file_table[fd].disk_offset + open_offset, real_len);
  file_table[fd].open_offset = open_offset + real_len;

  return ret;
}

size_t fs_write(int fd, const void *buf, size_t len) {
  
  size_t ret = 0;
  if (file_table[fd].write) {
    // Log("write ");
    return file_table[fd].write(buf, file_table[fd].open_offset , len);
  } else {
    assert(file_table[fd].open_offset + len <= file_table[fd].size);
    ret = ramdisk_write(buf, file_table[fd].disk_offset + file_table[fd].open_offset, len);
    file_table[fd].open_offset += len;
  }
  return ret;
}

size_t fs_lseek(int fd, size_t offset, int whence) {
  size_t cur_offset = file_table[fd].open_offset;

  switch (whence) {
    case SEEK_SET:
      assert(offset <= file_table[fd].size);
      file_table[fd].open_offset = offset;
      break;
    case SEEK_CUR:
      assert(cur_offset + offset <= file_table[fd].size);
      file_table[fd].open_offset = cur_offset + offset;
      break;
    case SEEK_END:
      assert(file_table[fd].size + offset <= file_table[fd].size);
      file_table[fd].open_offset =  file_table[fd].size + offset;
      break;
    default:
      break;
    }
    return file_table[fd].open_offset;
}

int fs_close(int fd){
  return 0;
}