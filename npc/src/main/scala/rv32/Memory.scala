package rv32

import chisel3._
import chisel3.util._
import Parameters._

class ImemPortIo extends Bundle{
    val addr = Input(UInt(WORD_LEN.W))
    val inst = Output(UInt(WORD_LEN.W))
}
class DmemPortIo extends Bundle{
    val addr = Input(UInt(WORD_LEN.W))
    val data = Input(UInt(WORD_LEN.W))
    val wen = Input(Bool())
    val rdata = Output(UInt(WORD_LEN.W))
}
class Memory extends Module{
    val io = IO(new Bundle{
        val imem = new ImemPortIo
        val dmem = new DmemPortIo
    })
    val mem = Mem(MEM_SIZE,UInt(MEM_WITH.W))
    io.imem.inst := Cat(mem(io.imem.addr),mem(io.imem.addr+1.U),mem(io.imem.addr+2.U),mem(io.imem.addr+3.U))
    when(io.dmem.wen){
        mem(io.dmem.addr) := io.dmem.data(7,0)
        mem(io.dmem.addr+1.U) := io.dmem.data(15,8)
        mem(io.dmem.addr+2.U) := io.dmem.data(23,16)
        mem(io.dmem.addr+3.U) := io.dmem.data(31,24)
    }
    io.dmem.rdata := Cat(mem(io.dmem.addr),mem(io.dmem.addr+1.U),mem(io.dmem.addr+2.U),mem(io.dmem.addr+3.U))
}