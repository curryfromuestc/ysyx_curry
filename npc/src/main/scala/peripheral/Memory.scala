package peripheral

import chisel3._
import chisel3.util._
import riscv.Parameters

class RAMBundle extends Bundle {
    val address = Input(UInt(Parameters.AddrWidth))
    val read_data = Output(UInt(Parameters.DataWidth))
    val write_data = Input(UInt(Parameters.DataWidth))
    val write_enable = Input(Bool())
    val write_strobe = Input(Vec(Parameters.WordSize, Bool())) // strobe is a mask, 是一个掩码
}

class Memory(capacity: Int) extends Module {
    val io = IO(new Bundle {
        val bundle = new RAMBundle // 当要读写内存中的内容为数据，IO接口使用RAMBundle
        // 当用读写内存中的内容为指令时，IO接口使用下面的接口
        val instruction_address = Input(UInt(Parameters.AddrWidth)) // 指令地址
        val instruction = Output(UInt(Parameters.DataWidth)) // 指令
        val debug_read_address = Input(UInt(Parameters.AddrWidth))
        val debug_read_data = Output(UInt(Parameters.DataWidth))
    })
    // SyncReadMem是一个同步读内存, 第一个参数是容量, 第二个参数是数据类型
    val mem = SyncReadMem(capacity, Vec(Parameters.WordSize, UInt(Parameters.ByteWidth)))
    when(io.bundle.write_enable) {
        // 定义write_data_vec为一个Vec, 它的每个元素是一个UInt(Parameters.ByteWidth)类型的数据
        val write_data_vec = Wire(Vec(Parameters.WordSize, UInt(Parameters.ByteWidth)))
        for (i <- 0 until Parameters.WordSize) {
            // 填充write_data_vec, 通过循环将write_data的每个字节分别赋值给write_data_vec
            write_data_vec(i) := io.bundle.write_data((i + 1) * Parameters.ByteBits - 1, i * Parameters.ByteBits)
        }
        // mem.write的第一个参数是地址, 第二个参数是数据, 第三个参数是掩码
        mem.write((io.bundle.address >> 2.U).asUInt, write_data_vec, io.bundle.write_strobe)
    }
    io.bundle.read_data := mem.read((io.bundle.address >> 2.U).asUInt, true.B).asUInt
    io.debug_read_data := mem.read((io.debug_read_address >> 2.U).asUInt, true.B).asUInt
    io.instruction := mem.read((io.instruction_address >> 2.U).asUInt, true.B).asUInt
}