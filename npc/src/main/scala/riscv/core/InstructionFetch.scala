package riscv.core

import chisel3._
import riscv.Parameters

object ProgramCounter {
    val EntryAddress = Parameters.EntryAddress
}

class InstructionFetch extends Module {
    val io = IO(new Bundle{
        val jump_flag_id = Input(Bool()) // 跳转标志
        val jump_address_id = Input(UInt(Parameters.AddrWidth)) // 跳转地址
        val instruction_read_data = Input(UInt(Parameters.DataWidth)) // 从内存中读取的指令
        val instruction_valid = Input(Bool())  // 指令有效信号

        val instruction_address = Output(UInt(Parameters.AddrWidth)) // 指令地址
        val instruction = Output(UInt(Parameters.InstructionWidth)) // 指令
    })

    // 首先，PC寄存器的值初始化为程序的入口地址
    val pc = RegInit(ProgramCounter.EntryAddress)

    when(io.instruction_valid) {
        io.instruction := io.instruction_read_data // 指令有效时，输出从内存中读取的指令
        // 1. 根据当前PC寄存器的地址从内存中取出指令
        // 2. 修改PC寄存器的值使其指向下一条指令
        //    - 需要跳转，则PC指向跳转地址
        //    - 顺序执行，则PC += 4
        // 3. 将PC的值输出到io.instruction_address中
        when(io.jump_flag_id) {
            pc := io.jump_address_id
        }.otherwise {
            pc := pc + 4.U
        }
    }.otherwise {
        // 当前PC执行的指令无效，输出NOP指令
        pc := pc
        io.instruction := 0x0000_0013.U
    }
    io.instruction_address := pc
}