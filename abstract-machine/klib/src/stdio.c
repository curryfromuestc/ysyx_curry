#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)


static void reverse(char *s, int len) {
  int time=len/2;
  int cur_time=0;
  char *end = s + len - 1;
  char tmp;
  while (cur_time < time) {
    tmp = *s;
    *s = *end;
    *end = tmp;
    s++;
    end--;
    cur_time++;
  }
}

/* itoa convert int to string under base. return string length */
static int itoa(int n, char *s, int base) {
  assert(base <= 16);
  if(n!=-2147483648 && n!=0){
  int i = 0, sign = n, bit;
  if (sign < 0) n = -n;
  while (n > 0 ){
    bit = n % base;
    if (bit >= 10) s[i++] = 'a' + bit - 10;
    else s[i++] = '0' + bit;
    n=n/base;
    
  } 

  if (sign < 0) s[i++] = '-';
  s[i] = '\0';

  reverse(s, i);

  return i;}
  else if(n==0)
  {strcpy(s, "0");
  return 1;}
  else{strcpy(s, "-2147483648");
  return 11;}
}


int sprintf(char *out, const char *fmt, ...) {
  va_list pArgs;
  va_start(pArgs, fmt);
  char *start = out;

  for (; *fmt != '\0'; ++fmt) {
    
    if (*fmt != '%') {
      *out = *fmt;
      ++out;
    } else {
      switch (*(++fmt)) {
      case '%': *out = *fmt; ++out; break;
      case 'd': out += itoa(va_arg(pArgs, int), out, 10); break;
      case 's':
        char *s = va_arg(pArgs, char*);
        strcpy(out, s);
        out += strlen(out);
        break;
      case 'c':
        char yy=va_arg(pArgs, int);
        *out = yy;
        out += 1;
        break;
      }
      
    }
    
  }
  *out = '\0';
  va_end(pArgs);

  return out - start;
}


int printf(const char *fmt, ...) {
  char info[256];
  for(int i=0;i<256;i++)
  {
    info[i]='\0';
  }
  char *buffer = info;

  va_list pArgs;
  va_start(pArgs, fmt);
  char *start = buffer;
  char *start_count = start;

   for (; *fmt != '\0'; ++fmt) {
    if (*fmt != '%') {
      *buffer = *fmt;
      ++buffer;
    } else {
      switch (*(++fmt)) {
      case '%': *buffer = *fmt; ++buffer; break;
      case 'd': buffer += itoa(va_arg(pArgs, int), buffer, 10); break;
      case 'x': buffer += itoa(va_arg(pArgs, int), buffer, 16); break;
      case 'l': switch(*(++fmt)){
        case 'x':buffer += itoa(va_arg(pArgs,unsigned long int), buffer, 16); break;
        case 'd':buffer += itoa(va_arg(pArgs,unsigned long int), buffer, 10); break;
        default : putch('e');putch('\n');putch(*fmt);putch('\n');
                  panic("\nprintf not all long\n");
      }break;
      case '0': ++fmt; int num_0 = *fmt - '0'; ++fmt; int argsn = va_arg(pArgs, int);
                if((*fmt!='x') && (*fmt!='d')){
                  putch('e');putch('\n');putch(*fmt);putch('\n');
                  panic("\nprintf 0x or 0d\n");
                }
                else if(*fmt=='x'){
                  if(itoa(argsn, buffer, 16)<num_0){
                    for(int i=0;i<num_0-itoa(argsn, buffer, 16);i++){
                      *buffer = '0';buffer++;
                    }
                  }
                  buffer += itoa(argsn, buffer, 16);
                }
                else if(*fmt=='d'){
                  if(itoa(argsn, buffer, 10)<num_0){
                    for(int i=0;i<num_0-itoa(argsn, buffer, 10);i++){
                      *buffer = '0';buffer++;
                    }
                  }
                  buffer += itoa(argsn, buffer, 10);
                }
                break;
      case 's':
        char *s = va_arg(pArgs, char*);
        strcpy(buffer, s);
        buffer += strlen(buffer);
        break;
      case 'c':
        char yy=va_arg(pArgs, int);
        *buffer = yy;
        buffer += 1;
        break;
      default:
        if((*fmt-'0')>=0 && (*fmt-'0')<=9){
          int num_1 = *fmt - '0';fmt++;int argsn = va_arg(pArgs, int);
          if((*fmt!='x') && (*fmt!='d')){
            putch('e');putch('\n');putch(*fmt);putch('\n');
            panic("\nprintf 1x or 1d\n");
          }
          else if(*fmt=='x'){
            if(itoa(argsn, buffer, 16)<num_1){
              for(int i=0;i<num_1-itoa(argsn, buffer, 16);i++){
                *buffer = ' ';buffer++;
              }
            }
            buffer += itoa(argsn, buffer, 16);
          }
          else if(*fmt=='d'){
            if(itoa(argsn, buffer, 10)<num_1){
              for(int i=0;i<num_1-itoa(argsn, buffer, 10);i++){
                *buffer = ' ';buffer++;
              }
            }
            buffer += itoa(argsn, buffer, 10);
          }
        }
        else{
          putch('e');putch('\n');putch(*fmt);putch('\n');
          panic("\nprintf not all geshihua\n");
        }
      }
    }
  }
  *buffer = '\0';
  va_end(pArgs);

    
    // 逐个字符输出
    while(*start!='\0'){
      putch(*start);
      start++;
    }

    return buffer-start_count;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}


int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif