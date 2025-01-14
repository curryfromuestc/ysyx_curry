package rv32i

import chisel3._
import chisel3.util._
import chisel3.util.experimental.loadMemoryFromFile

import config.Configs._
import firrtl.annotations.MemoryLoadFileType

class MemInstIO extends Bundle {
    val addr = Input(UInt(ADDR_WIDTH.W))
    val inst = Output(UInt(DATA_WIDTH.W))
}

class MemInst extends Module {
    val io = IO(new MemInstIO)

    val mem = Mem(MEM_INST_SIZE, UInt(INST_WIDTH.W))

    io.inst := mem.read(io.addr >> INST_BYTE_WIDTH_LOG.U)
}