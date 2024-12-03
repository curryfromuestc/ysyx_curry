/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// this should be enough
static char buf[65536] = {};
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() { \n"
"  unsigned result = %s; \n"
"  printf(\"%%u\", result); \n"
"  return 0; \n"
"}\n";

static int choose(int n) {
  return rand() % n;//返回一个0到n-1的随机数
}

static void gen_num() {
  sprintf(buf + strlen(buf), "%uu", (unsigned int)choose(100));
  buf[strlen(buf)] = '\0';
}

static void gen(char a) {
  sprintf(buf + strlen(buf), "%c", a);
  buf[strlen(buf)] = '\0';
}

static void gen_rand_op() {
  char opt = 0;
  switch (choose(4)) {
    case 0: opt = '+'; break;
    case 1: opt = '-'; break;
    case 2: opt = '*'; break;
    case 3: opt = '/'; break;
  }
  sprintf(buf + strlen(buf), "%c", opt);
  buf[strlen(buf)] = '\0';
}

static inline void gen_rand_expr() {
  if (strlen(buf) < 100) {
    switch (choose(3)) {
      case 0: gen_num(); break;
      case 1: gen('('); gen_rand_expr(); gen(')'); break;
      default: gen_rand_expr(); gen_rand_op(); gen_rand_expr(); break;
    }
  } else {
    gen_num();
  }
  buf[strlen(buf)] = '\0';
}

//之前在表达式里面添加了'u'，现在要去掉，不知道为啥，如果不加的话，输进去的表达式跟期望的不对
void remove_u(char *p) {
  char *q = p;
  while ((q = strchr(q, 'u')) != NULL) {
    strcpy(code_buf, q + 1);
    strcpy(q, code_buf);//覆盖'u'
  }
}

int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    memset(buf,0,sizeof(buf));//防止溢出
    gen_rand_expr();

    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system("gcc /tmp/.code.c -o /tmp/.expr");
    if (ret == -1) continue;//出现除0的情况，会导致错误，system返回的是-1，这里条件就不满足了，直接continue

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    ret = fscanf(fp, "%d", &result);
    if (ret != 1) continue;//不为1说明读取失败，说明读取了多个整数结果
    ret = pclose(fp);
    if (ret == -1) continue;//关闭失败

    remove_u(buf);

    printf("%u %s\n", result, buf);
  }
  return 0;
}