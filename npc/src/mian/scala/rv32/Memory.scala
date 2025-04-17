package rv32

import chisel3._
import chisel3.util._
import Parameters._

class ImemPortIo extends Bundle{
    val addr = Input(UInt(WORD_LEN.W))
    val inst = Output(UInt(WORD_LEN.W))
}
class Memory(hexMemFile: String) extends Module{
    val io = IO(new ImemPortIo)
    val mem = Mem(1024,UInt(WORD_LEN.W))
    io.inst := mem(io.addr)
}