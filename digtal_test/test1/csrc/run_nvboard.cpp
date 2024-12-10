# include <nvboard.h>
# include <Vtop.h>

static TOP_NAME dut;

void nvboard_bind_all_pins(TOP_NAME* top);

int main(){
    nvboard_bind_all_pins(&dut);
    nvboard_init();
    dut.Y = 0b00;
    dut.X0 = 0b01;
    dut.X1 = 0b10;
    dut.X2 = 0b11;
    dut.X3 = 0b00;
    while(1){
        nvboard_update();
        dut.eval();
    }
}