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
    dut -> en = 0b0;
    dut -> x = 0b00000000;
    step_and_dump_wave();
    dut -> en = 0b0;
    dut -> x = 0b00000001;
    step_and_dump_wave();
    dut -> en = 0b0;
    dut -> x = 0b00000010;
    step_and_dump_wave();
    dut -> en = 0b0;
    dut -> x = 0b00000100;
    step_and_dump_wave();
    dut -> en = 0b0;
    dut -> x = 0b00001000;
    step_and_dump_wave();
    dut -> en = 0b0;
    dut -> x = 0b00010000;
    step_and_dump_wave();
    dut -> en = 0b0;
    dut -> x = 0b00100000;
    step_and_dump_wave();
    dut -> en = 0b0;
    dut -> x = 0b01000000;
    step_and_dump_wave();
    dut -> en = 0b0;
    dut -> x = 0b10000000;
    step_and_dump_wave();

    dut -> en = 0b1;
    dut -> x = 0b00000000;
    step_and_dump_wave();
    dut -> en = 0b1;
    dut -> x = 0b00000001;
    step_and_dump_wave();
    dut -> en = 0b1;
    dut -> x = 0b00000010;
    step_and_dump_wave();
    dut -> en = 0b1;
    dut -> x = 0b00000100;
    step_and_dump_wave();
    dut -> en = 0b1;
    dut -> x = 0b00001000;
    step_and_dump_wave();
    dut -> en = 0b1;
    dut -> x = 0b00010000;
    step_and_dump_wave();
    dut -> en = 0b1;
    dut -> x = 0b00100000;
    step_and_dump_wave();
    dut -> en = 0b1;
    dut -> x = 0b01000000;
    step_and_dump_wave();
    dut -> en = 0b1;
    dut -> x = 0b10000000;
    step_and_dump_wave();
    sim_finish();
}

