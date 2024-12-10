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
    dut->Y = 0b00;
    dut->X0 = 0b00;
    dut->X1 = 0b00;
    dut->X2 = 0b00;
    dut->X3 = 0b00;
    step_and_dump_wave();
    dut->Y = 0b01;
    dut->X0 = 0b01;
    dut->X1 = 0b01;
    dut->X2 = 0b01;
    dut->X3 = 0b01;
    step_and_dump_wave();
    dut->Y = 0b10;
    dut->X0 = 0b10;
    dut->X1 = 0b10;
    dut->X2 = 0b10;
    dut->X3 = 0b10;
    step_and_dump_wave();
    sim_finish();
}

