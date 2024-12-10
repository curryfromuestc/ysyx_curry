# include <verilated.h>
# include <Vtop.h>
# include <verilated_vcd_c.h>
# include <iostream>

VerilatedContext* contextp = NULL;
VerilatedVcdC* tfp = NULL;

static Vtop* dut;

void step_and_dump_wave(){
    dut->eval();
    contextp->timeInc(1);
    tfp->dump(contextp->time());
}

void sim_init(){
    contextp = new VerilatedContext;
    tfp = new VerilatedVcdC;
    dut = new Vtop;
    contextp->traceEverOn(true);
    dut->trace(tfp, 0);
    tfp->open("wave.vcd");
}

void sim_finish(){
    step_and_dump_wave();
    tfp->close();
}

int main(int argc,char *argv[]){
    sim_init();
    //在op分别为000，001，010，011，100，101，110，111时，进行10组随机测试，也就是输入的a和b均为随机的4为有符号数
    for (int i =0;i<8;i++){
        dut->op = i & 0b111;
        dut->a = rand() & 0b1111;
        dut->b = rand() & 0b1111;
        printf("op = %d, a = %d, b = %d\n",dut->op,dut->a,dut->b);
        step_and_dump_wave();
        printf("result = %d\n",dut->y);
        
    }
    sim_finish();
}

