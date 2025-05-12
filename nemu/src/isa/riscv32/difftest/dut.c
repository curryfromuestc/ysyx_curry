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
#include <cpu/difftest.h>
#include "../local-include/reg.h"

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  int reg_num = ARRLEN(cpu.gpr);
  for (int i = 0; i < reg_num; i++) {
      if (ref_r->gpr[i] != cpu.gpr[i]) {
          printf("reg[%d] is different! ref: 0x%08x, current: 0x%08x\n", i, ref_r->gpr[i], cpu.gpr[i]);
          return false;
      }
  }
  if (ref_r->pc != cpu.pc) {
      printf("pc is different! ref: 0x%08x, current: 0x%08x\n", ref_r->pc, cpu.pc);
      return false;
  }
  if (ref_r->csrs.mstatus != cpu.csrs.mstatus) {
      printf("mstatus is different! ref: 0x%08x, current: 0x%08x\n", ref_r->csrs.mstatus, cpu.csrs.mstatus);
      return false;
  }
  if (ref_r->csrs.mcause != cpu.csrs.mcause) {
      printf("mcause is different! ref: 0x%08x, current: 0x%08x\n", ref_r->csrs.mcause, cpu.csrs.mcause);
      return false;
  }
  if (ref_r->csrs.mepc != cpu.csrs.mepc) {
      printf("mepc is different! ref: 0x%08x, current: 0x%08x\n", ref_r->csrs.mepc, cpu.csrs.mepc);
      return false;
  }
  if (ref_r->csrs.mtvec != cpu.csrs.mtvec) {
      printf("mtvec is different! ref: 0x%08x, current: 0x%08x\n", ref_r->csrs.mtvec, cpu.csrs.mtvec);
      return false;
  }
  return true;
}
