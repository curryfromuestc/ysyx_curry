#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  if (s == NULL) {
    return 0;
  }
  size_t len = 0;
  while (s[len] != '\0') {
    len++;
  }
  return len;
}

char *strcpy(char *dst, const char *src) {
  //panic("Not implemented");
  assert(dst != NULL && src != NULL);

  char *tmp = dst;

  while(*src != '\0')
  {
    *tmp++ = *src++;
  }
  *tmp = '\0';
  
  return dst;
}


char *strncpy(char *dst, const char *src, size_t n) {
  size_t i = 0;
  for(i = 0; src[i] != '\0'; i++){
    dst[i] = src[i];
  }

  dst[i] = '\0';
  return dst;
}

char *strcat(char *dst, const char *src) {
  size_t len = strlen(dst);
  strcpy(dst + len, src);
  return dst;
}

int strcmp(const char *s1, const char *s2) {
  while (*s1 != '\0' && *s2 != '\0') {
    if (*s1 != *s2) {
      return *s1 - *s2;
    }
    s1++;
    s2++;
  }
  return *s1 - *s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  size_t i = 0;
  while (i < n && s1[i] != '\0' && s2[i] != '\0') {
    if (s1[i] != s2[i]) {
      return s1[i] - s2[i];
    }
    i++;
  }
  if (i == n) {
    return 0;
  }
  return s1[i] - s2[i];
}

void *memset(void *s, int c, size_t n) {
  char *p = s;
  while (n-- > 0) {
    *p++ = c;
  }
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  if(dst < src)
  {
	  char *d = (char *) dst;
	  char *s = (char *) src;
	  while(n--)
	  {
		  *d = *s;
		  d++;
		  s++;
	  }
  }
  else
  {
	  char *d = (char *) dst + n - 1;
	  char *s = (char *) src + n - 1;
	  while(n--)
	  {
		  *d = *s;
		  d--;
		  s--;
	  }
  }
  return dst;
}

void *memcpy(void *out, const void *in, size_t n) {
  char *d = out;
  const char *s = in;
  while (n-- > 0) {
    *d++ = *s++;
  }
  return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  const unsigned char *p1 = s1;
  const unsigned char *p2 = s2;
  while (n-- > 0) {
    if (*p1 != *p2) {
      return *p1 - *p2;
    }
    p1++;
    p2++;
  }
  return 0;
}

#endif
