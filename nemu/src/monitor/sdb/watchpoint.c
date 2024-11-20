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

#include "watchpoint.h"
#include "sdb.h"

#define NR_WP 32

typedef struct watchpoint {
    int NO;
    struct watchpoint *next;

    // TODO: Add more members if necessary

    bool flag; 
    char expr[100];
    int new_value;
    int old_value;

} WP;


static WP wp_pool[NR_WP] ;

static WP *head ;
static WP *free_ ;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}



WP* new_wp(){
    for(WP* p = free_ ; p -> next != NULL ; p = p -> next){
        if( p -> flag == false){
            p -> flag = true;
            if(head == NULL){
                head = p;
            }
            return p;
        }
    }

    printf("No valid unused point.\n");
    assert(0);
    return NULL;

}



void free_wp(WP *wp){
    if(head -> NO == wp -> NO){
        head -> flag = false;
        head = NULL;
        printf("Delete watchpoint  success.\n");
        return ;
    }
    for(WP* p = head ; p -> next != NULL ; p = p -> next){
        if(p -> next -> NO  == wp -> NO)
        {
            p -> next -> flag = false; 
            p -> next = p -> next -> next;
            
            printf("free succes.\n");
            return ;
        }
    }
}


int wp_pool_flag(int i){
    return wp_pool[i].flag;
}

int wp_pool_old_value(int i){
    return wp_pool[i].old_value;
}


void wp_pool_write_new_value(int i,int value){
    wp_pool[i].new_value=value;
    return;
}


char* wp_pool_expr(int i){
    static char expre_str[100];
    strcpy(expre_str,wp_pool[i].expr);
    return expre_str;
}



void sdb_watchpoint_display(){
    bool flag = true;
    for(int i = 0 ; i < NR_WP ; i ++){
        if(wp_pool[i].flag){
            printf("Watchpoint.No: %d, expr = \"%s\", old_value = %x, new_value = %x\n",
                    wp_pool[i].NO, wp_pool[i].expr,wp_pool[i].old_value, wp_pool[i].new_value);
                flag = false;
        }
    }
    if(flag) printf("No watchpoint now.\n");
}



void delete_watchpoint(int no){
    for(int i = 0 ; i < NR_WP ; i ++)
        if(wp_pool[i].NO == no){
            free_wp(&wp_pool[i]);
            return ;
        }
}



void create_watchpoint(char* args){
    WP* p =  new_wp();
    strcpy(p -> expr, args);
    bool success = false;
    int tmp = expr(p -> expr,&success);
   if(success){
    p -> old_value = tmp;
    p -> new_value = tmp;
   }
   else printf("Invalid expression!\n");
    printf("Create watchpoint No.%d success.\n", p -> NO);
}