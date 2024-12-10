#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <iostream>

// PS/2 键盘协议参数
#define MAIN_TIME_MAX 2000000     // 最大仿真时间
#define SYS_CLK_PERIOD 10          // 系统时钟周期，单位 ns
#define PS2_CLK_PERIOD 1000         // PS/2 时钟周期，单位 ns

vluint64_t main_time = 0;  // 全局仿真时间

void send_ps2_byte(Vtop* top, uint8_t data_byte, VerilatedVcdC* tfp) {
    uint8_t send_buffer[11];
    int i;

    // 构建发送缓冲区
    send_buffer[0] = 0; // 起始位，逻辑0
    for (i = 1; i <= 8; ++i) {
        send_buffer[i] = (data_byte >> (i - 1)) & 0x1; // 数据位，低位在前
    }
    // 奇偶校验位，使用奇校验
    uint8_t parity = 0;
    for (i = 1; i <= 8; ++i) {
        parity ^= send_buffer[i];
    }
    send_buffer[9] = parity; // 奇偶校验位
    send_buffer[10] = 1;     // 停止位，逻辑1

    // 发送11位数据
    for (int bit_idx = 0; bit_idx < 11; ++bit_idx) {
        // 准备好数据位
        top->ps2_data = send_buffer[bit_idx];

        // PS/2 时钟下降沿
        top->ps2_clk = 0;

        // 在 PS/2 时钟的半个周期内，主时钟运行
        for (int time = 0; time < PS2_CLK_PERIOD / 2; time += SYS_CLK_PERIOD / 2) {
            top->clk = !top->clk;       // 切换主时钟
            top->eval();
            tfp->dump(main_time);
            main_time += SYS_CLK_PERIOD / 2;
        }

        // PS/2 时钟上升沿
        top->ps2_clk = 1;

        // 在 PS/2 时钟的半个周期内，主时钟运行
        for (int time = 0; time < PS2_CLK_PERIOD / 2; time += SYS_CLK_PERIOD / 2) {
            top->clk = !top->clk;       // 切换主时钟
            top->eval();
            tfp->dump(main_time);
            main_time += SYS_CLK_PERIOD / 2;
        }
    }

    // 发送完成后，释放数据线和时钟线
    top->ps2_data = 1;
    top->ps2_clk = 1;

    // 主时钟继续运行一段时间
    for (int i = 0; i < 200; ++i) {
        top->clk = !top->clk;
        top->eval();
        tfp->dump(main_time);
        main_time += SYS_CLK_PERIOD / 2;
    }
}
int main(int argc, char** argv) {
    Verilated::traceEverOn(true);
    Vtop* top = new Vtop;

    // 创建波形文件
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("wave.vcd");

    // 初始化信号
    top->clk = 0;
    top->clrn = 1; // 高电平复位
    top->ps2_clk = 1;
    top->ps2_data = 1;
    // 复位
    for (int i = 0; i < 20; ++i) {
        top->clk = !top->clk;
        top->eval();
        tfp->dump(main_time+=SYS_CLK_PERIOD/2);
    }
    top->clrn = 0; // 解除复位

    // 主仿真循环
    while (!Verilated::gotFinish() && main_time < MAIN_TIME_MAX) {
        // 切换主时钟
        top->clk = !top->clk;
        top->eval();
        tfp->dump(main_time);
        main_time += SYS_CLK_PERIOD / 2;

        // 在适当的时间点发送按键数据
        if (main_time == 10000) {
            // 发送按下 'A' 的扫描码 0x1C
            send_ps2_byte(top, 0x1C, tfp);
        }
        if (main_time == 50000) {
            // 发送释放键的前缀码 0xF0
            send_ps2_byte(top, 0xF0, tfp);
            // 发送释放 'A' 的扫描码 0x1C
            send_ps2_byte(top, 0x1C, tfp);
        }
    }

    // 结束仿真
    tfp->close();
    delete top;
    delete tfp;
    return 0;
}