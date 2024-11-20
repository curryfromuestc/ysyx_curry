#ifndef WATCHPOINT_H
#define WATCHPOINT_H

#include "sdb.h"

#define NR_WP 32




void init_wp_pool();
void sdb_watchpoint_display();
void delete_watchpoint(int no);
void create_watchpoint(char* args);
int wp_pool_flag(int i);
int wp_pool_old_value(int i);
char *wp_pool_expr(int i);
void wp_pool_write_new_value(int i,int value);


#endif