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
    val mem = Mem(1024,UInt(WORD_LEN.W))
    io.imem.inst := mem(io.imem.addr)
    when(io.dmem.wen){
        mem(io.dmem.addr) := io.dmem.data
    }
    io.dmem.rdata := mem(io.dmem.addr)
}