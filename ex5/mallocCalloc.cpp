#include <sys/mman.h>
#include <stdio.h>

void* mymalloc(size_t len) {
  void* addr = mmap(0,
                    len + sizeof(size_t),
                    PROT_READ | PROT_WRITE,
                    MAP_ANON | MAP_SHARED ,
                    -1,
                    0);
  *(size_t*)addr = len;
  return (int*)addr + sizeof(size_t);
}

int myfree(void* addr) {
  return munmap((int*)addr - sizeof(size_t), (size_t) addr);
}