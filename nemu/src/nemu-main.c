/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
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

#include <common.h>



void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();

word_t expr(char *e, bool *success);
void init_regex();
void test_expr() {
  char line[256];
  FILE *file = fopen("/home/curry/code/ysyx_curry/nemu/tools/gen-expr/input", "r");

  if (file == NULL) {
    printf("Could not open file input\n");
    return;
  }

  while (fgets(line, sizeof(line), file)) {
    char *expected_str = strtok(line, " ");
    char *expr_str = strtok(NULL, "\n");

    bool success = true;
    int expected = atoi(expected_str);//将字符串转换为整数
    int result = expr(expr_str, &success);

    if (success) {
        printf("Expression: %s, Expected: %d, Got: %d\n", expr_str, expected, result);
        if (expected != result) {
            printf("Test failed!\n");
            assert(0);
        }
    } else {
        printf("Failed to evaluate expression: %s\n", expr_str);
    }
  }

  fclose(file);
}

int main(int argc, char *argv[]) {
  /* Initialize the monitor. */
#ifdef CONFIG_TARGET_AM
  am_init_monitor();
  test_expr();
#else
  init_monitor(argc, argv);
  //test_expr();
#endif

  /* Start engine. */
  engine_start();

  return is_exit_status_bad();
}
