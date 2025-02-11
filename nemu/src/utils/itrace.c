#include "local-include/itrace.h"
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>

ItraceNode iringbuf[MAX_IRINGBUF];
int p_cur = 0;
bool full = false;

void trace_inst(word_t pc, uint32_t inst) {
  iringbuf[p_cur].pc = pc;
  iringbuf[p_cur].inst = inst;
  p_cur = (p_cur + 1) % MAX_IRINGBUF;
  full = full || p_cur == 0;
}

void display_inst() {
    if ((full == false)&&(p_cur == 0)) return;

    int end = p_cur;
    int i = full? p_cur :0;

    char buf[128];
    char *p;
    printf("recent instructions:\n");
    do {
      p = buf;
      p += sprintf(buf, "%s" FMT_WORD ":%08x", (i + 1)%MAX_IRINGBUF == end?"-->":"   ", iringbuf[i].pc, iringbuf[i].inst);
      disassemble(p, buf+sizeof(buf)-p, iringbuf[i].pc, (uint8_t *)&iringbuf[i].inst, 4);

      if((i+1)%MAX_IRINGBUF == end){
        printf(ANSI_FG_RED);
      }
      puts(buf);
    }while((i = (i + 1) % MAX_IRINGBUF) != end);
    puts(ANSI_NONE);
}

//mtrace
void display_pread(paddr_t addr, int len) {
  printf("pread at " FMT_PADDR " len=%d\n", addr, len);
}

void display_pwrite(paddr_t addr, int len, word_t data) {
  printf("pwrite at " FMT_PADDR " len=%d, data=" FMT_WORD "\n", addr, len, data);
}

typedef struct {
  char name[32];
  paddr_t addr;
  unsigned char info;
  Elf32_Xword size;
} Symentry;

Symentry *symbol_tbl = NULL;
int symbol_tbl_size = 0;
int call_depth = 0;

typedef struct tail_rec_node {
	paddr_t pc;
	paddr_t depend;
	struct tail_rec_node *next;
} TailRecNode;
TailRecNode *tail_rec_head = NULL; 

static void read_elf_header(int fd, Elf32_Ehdr *eh) {
	assert(lseek(fd, 0, SEEK_SET) == 0);
  assert(read(fd, (void *)eh, sizeof(Elf32_Ehdr)) == sizeof(Elf64_Ehdr));

// check if is elf using fixed format of Magic: 7f 45 4c 46 ...
  if(strncmp((char*)eh->e_ident, "\177ELF", 4)) {
		panic("malformed ELF file");
	}
}

static void ftrace_write(const char *format, ...) {
  FILE *fp = fopen()
}

static void display_elf_header(Elf32_Ehdr eh) {
  ftrace_write("Storage class\t= ");
}

void trace_func_call(paddr_t pc, paddr_t target){

}

void trace_func_ret(paddr_t pc){
  
}