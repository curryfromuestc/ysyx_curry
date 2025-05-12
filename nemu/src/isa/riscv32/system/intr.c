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

#include <isa.h>

word_t isa_raise_intr(word_t NO, vaddr_t epc) {
  // mstatus set
  cpu.csrs.mstatus &= ~(1<<7);
  cpu.csrs.mstatus |= ((cpu.csrs.mstatus&(1<<3))<<4);
  cpu.csrs.mstatus &= ~(1<<3);
  cpu.csrs.mstatus |= ((1<<11)+(1<<12));

  // store pc in mepc
  cpu.csrs.mepc = epc; 
  // set err number in mcause
  cpu.csrs.mcause = NO;
  // get the address of the interrupt/exception vector and set pc to it
  return cpu.csrs.mtvec;
}



word_t isa_query_intr() {
  return INTR_EMPTY;
}
