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
#include <isa.h> 
#include "../../isa/riscv32/local-include/reg.h"
/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>
#define TestCorrect(x) if(x){printf("Invalid Command!\n");return 0;}

const char *regs1[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

enum {
	NOTYPE = 256, EQ, NUMBER, HEXNUMBER, REGISTER, NEQ, AND, OR, NOT, MINUS,POINTER,PC

	/* TODO: Add more token types */

};
static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */
	{" +",	NOTYPE},				// spaces
	{"\\+", '+'},					// plus
	{"==", EQ},						// equal
	{"!=", NEQ},
	{"!", NOT},
	{"&&", AND},
	{"\\|\\|", OR},
	{"\\$[a-zA-z]+", REGISTER},		// register
	{"\\pc", PC},
	{"\\b0[xX][0-9a-fA-F]+\\b", HEXNUMBER}, // hexnumber
	{"\\b[0-9]+\\b", NUMBER},				// number
	{"-", '-'},						// minus
	{"\\*", '*'},					// multiply
	{"/", '/'},						// divide
	{"\\(", '('},					// left bracket
	{"\\)", ')'},					// right bracket
	//{"\\b[a-zA-Z0-9_]+\\b",MARK},
};
#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

 

static Token tokens[1024] __attribute__((used)) = {};//1024
static int nr_token __attribute__((used))  = 0;
 

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch; 
  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
          	case NOTYPE: break;
				default: {
					tokens[nr_token].type = rules[i].token_type;
					if (rules[i].token_type == REGISTER) { //Register
						char* reg_start = e + (position - substr_len) + 1;
						strncpy(tokens[nr_token].str, reg_start, substr_len - 1);
						int t;
						for (t = 0; t <= strlen(tokens[nr_token].str); t++) { // tolower
							int x = tokens[nr_token].str[t];
							if (x >= 'A' && x <= 'Z') x += ('a' - 'A');
							tokens[nr_token].str[t] = (char)x;
						}
					} 
					else if (rules[i].token_type == PC)
					{
						strcpy(tokens[nr_token].str, "pc");
					}else
					{
						strncpy(tokens[nr_token].str, substr_start, substr_len);
					}
						tokens[nr_token].str[substr_len] = '\0';
						nr_token ++;
				}
				}

		 
        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}


bool check_bracket(int l, int r) {
	if (tokens[l].type != '(' || tokens[r].type != ')') return false;
	int b_num = 0, i;
	for (i = l; i <= r; i ++) {
		if (tokens[i].type == '(') b_num ++;
		if (tokens[i].type == ')') b_num --;
		if (b_num == 0 && i != r) return false;
	}
	if (b_num == 0) return true;
	return false;
}

int dominant_op(int l, int r) {
	int i;
	int pos = l;
	int pri = 0;
	int b_num = 0;
	for (i = r; i >= l; i --) {
		if (tokens[i].type == ')') b_num++;
		if (tokens[i].type == '(') b_num--;
		if (b_num != 0) continue;
		switch (tokens[i].type) {
		case '+': { // pri = 4
			if (pri < 4) pos = i, pri = 4;
			break;
		}
		case '-': { // pri = 4
			if (pri < 4) pos = i, pri = 4;
			break;
		}
		case '*': { // pri = 3
			if (pri < 3) pos = i, pri = 3;
			break;
		}
		case '/': { // pri = 3
			if (pri < 3) pos = i, pri = 3;
			break;
		}
		case NOT: { // pri = 2
			if (pri < 2) pos = i, pri = 2;
			break;
		}
		case EQ: { // pri = 7
			if (pri < 7) pos = i, pri = 7;
			break;
		}
		case NEQ: { // pri = 7
			if (pri < 7) pos = i, pri = 7;
			break;
		}
		case AND: { // pri = 11
			if (pri < 11) pos = i, pri = 11;
			break;
		}
		case OR: { // pri = 12
			if (pri < 12) pos = i, pri = 12;
			break;
		}
		case POINTER:{
			if (pri <2) pos = i, pri = 2;
			break;
		}
		default: break;
		}
	}
//	printf("%d-%d %d %d\n",l,r,pos,pri);
	if (pri == 0) {
		return 0;
		}

	if (pri == 2) {
		pri = 0;
		for (i = l; i <= r; i ++) {
			if (tokens[i].type == '(') b_num++;
			if (tokens[i].type == ')') b_num--;
			if (b_num != 0) continue;
			switch (tokens[i].type) {
			case NOT: { // pri = 2
				if (pri < 2) pos = i, pri = 2;
				break;
			}
			case POINTER:{
				if (pri <2) pos = i, pri = 2;
				break;
			}
		}
	}
	}
	return pos;
}
uint32_t eval(int l, int r) {
	if (l > r) {
		return 0;
	}
	if (l == r) {
		uint32_t num = 0;
		if (tokens[l].type == NUMBER) {
			sscanf(tokens[l].str, "%d", &num);
		} else if (tokens[l].type == HEXNUMBER) {
			sscanf(tokens[l].str, "%x", &num);
		}
		else if (tokens[l].type == REGISTER) {
			int i =0;
			for ( i = 0; i < 32; i++)
			{
				if (strcmp(tokens[l].str, regs1[i]) == 0)
				{
					printf("%d\n",i);
					printf(ANSI_FG_GREEN"%-3s: "ANSI_FG_MAGENTA FMT_WORD" "ANSI_NONE, regs1[i], cpu.gpr[i]);
					//return gpr(i);
				}
			}
			
		} 
		else if (tokens[l].type == PC)
		{
			printf(ANSI_FG_RED"%-3s: "ANSI_FG_MAGENTA FMT_WORD ANSI_NONE"\n", "$pc", cpu.pc);
			return cpu.pc;
		}
		else {return 0;}
		return num;
	}
	uint32_t ans = 0;

	if (check_bracket(l, r)) return eval(l + 1, r - 1);
	else {
		int pos = dominant_op(l, r);
		if (l == pos || tokens[pos].type == NOT) {
			uint32_t r_ans = eval(pos + 1, r);
			switch (tokens[pos].type) {
			case NOT: return !r_ans;
			default: {return 0;}
			}
		}
		uint32_t l_ans = eval(l, pos - 1), r_ans =  eval(pos + 1, r);
		switch (tokens[pos].type) {
		case '+': ans = l_ans + r_ans; break;
		case '-': ans = l_ans - r_ans; break;
		case '*': ans = l_ans * r_ans; break;
		case '/': if (r_ans == 0) {return 0;} else ans = l_ans / r_ans; break;
		case EQ : ans = l_ans == r_ans; break;
		case NEQ: ans = l_ans != r_ans; break;
		case AND: ans = l_ans && r_ans; break;
		case OR : ans = l_ans && r_ans; break;
		default: {return 0;}
		}
	}
	return ans;
}

uint32_t expr(char *e, bool *success) {
	if (!make_token(e)) {
		*success = false;
		return 0;
	}
	/* TODO: Insert codes to evaluate the expression. */
	/*check whether brackets are matched*/
	int i, brack = 0;
	for (i = 0; i < nr_token ; i++) {
		if (tokens[i].type == '(') brack ++;
		if (tokens[i].type == ')') brack --;
		if (brack < 0) {
			*success = false;
			return 0;
		}
		if (tokens[i].type == '*' && (i == 0 || (tokens[i - 1].type != ')' && tokens[i - 1].type != NUMBER && tokens[i - 1].type != HEXNUMBER && tokens[i - 1].type != REGISTER))) {
			tokens[i].type = POINTER;
		}
	}
	if (brack != 0) {
		*success = false;
		return 0;
	}

//	panic("please implement me");
	*success = true;
	uint32_t sum1=0;
	sum1=eval(0, nr_token - 1);
	return sum1;
}