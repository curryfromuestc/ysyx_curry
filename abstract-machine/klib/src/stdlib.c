#include <am.h>
#include <klib.h>
#include <klib-macros.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
static unsigned long int next = 1;

int rand(void) {
  // RAND_MAX assumed to be 32767
  next = next * 1103515245 + 12345;
  return (unsigned int)(next/65536) % 32768;
}

void srand(unsigned int seed) {
  next = seed;
}

int abs(int x) {
  return (x < 0 ? -x : x);
}

int atoi(const char* nptr) {
  int x = 0;
  while (*nptr == ' ') { nptr ++; }
  while (*nptr >= '0' && *nptr <= '9') {
    x = x * 10 + *nptr - '0';
    nptr ++;
  }
  return x;
}

// extern char _heap_start;
// #define PMEM_SIZE (128 * 1024 * 1024)
// #define PMEM_END ((uintptr_t)0x80000000 + PMEM_SIZE)

// Area heap = RANGE(&_heap_start, PMEM_END);
int reset_yet=0;
__attribute__((unused)) static char *hbrk;
__attribute__((unused)) static void heap_reset() {
  hbrk = (void *)ROUNDUP(heap.start, 8);
}

void *malloc(size_t size) {
  // On native, malloc() will be called during initializaion of C runtime.
  // Therefore do not call panic() here, else it will yield a dead recursion:
  //   panic() -> putchar() -> (glibc) -> malloc() -> panic()
//#if !(defined(__ISA_NATIVE__) && defined(__NATIVE_USE_KLIB__))
  if(!reset_yet){
    heap_reset();
    reset_yet+=1;
    if(reset_yet!=1)
    panic("reset many times\n");
  }
  size  = (size_t)ROUNDUP(size, 8);
  char *old = hbrk;
  hbrk += size;
  assert((uintptr_t)heap.start <= (uintptr_t)hbrk && (uintptr_t)hbrk < (uintptr_t)heap.end);
  assert((uintptr_t)heap.start <= ((uintptr_t)hbrk+size) && ((uintptr_t)hbrk+size) < (uintptr_t)heap.end);
  for (uint64_t *p = (uint64_t *)old; p != (uint64_t *)hbrk; p ++) {
    *p = 0;
  }
  return old;
//#endif
  return NULL;
}

void free(void *ptr) {
}

#endif
