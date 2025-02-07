#include <common.h>

#define MAX_IRINGBUF 16

typedef struct {
    word_t pc;
    uint32_t inst;
} ItraceNode;

void trace_inst(word_t pc, uint32_t inst);
void display_inst();
void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);

//mtrace
void display_pread(paddr_t addr, int len);
void display_pwrite(paddr_t addr, int len, word_t data);

//ftrace
void trace_func_call(paddr_t pc, paddr_t target);
void trace_func_ret(paddr_t pc);
