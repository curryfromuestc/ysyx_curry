package riscv.core

import chisel3._
import chisel3.util._
import peripheral.RAMBundle
import riscv.Parameters

// 内存访问控制模块， 作为Memory模块的上层模块
class MemoryControl extends Module {
  val io = IO(new Bundle() {
    val alu_result = Input(UInt(Parameters.DataWidth)) // ALU计算结果，作为内存访问的地址
    val reg2_data = Input(UInt(Parameters.DataWidth))  // 寄存器堆的第二个寄存器的值，作为内存写入的数据
    val memory_read_enable = Input(Bool())  // 是否使能内存读
    val memory_write_enable = Input(Bool()) // 是否使能内存写
    val funct3 = Input(UInt(3.W))  // 功能码

    val wb_memory_read_data = Output(UInt(Parameters.DataWidth)) // 从内存中读取的数据

    val memory_bundle = Flipped(new RAMBundle) // 内存接口
  })
  val mem_address_index = io.alu_result(log2Up(Parameters.WordSize) - 1, 0).asUInt // 内存地址的索引，log2Up对数向上取整是为了防止内存地址不是字节对齐的情况

  io.memory_bundle.write_enable := false.B // 默认不使能内存写
  io.memory_bundle.write_data := 0.U  // 默认写入0
  io.memory_bundle.address := io.alu_result // 内存地址为ALU计算结果
  io.memory_bundle.write_strobe := VecInit(Seq.fill(Parameters.WordSize)(false.B)) // 默认写入0
  io.wb_memory_read_data := 0.U // 默认读取0

  when(io.memory_read_enable) { // 当使能内存读时，从内存中读取数据
    val data = io.memory_bundle.read_data // 从内存中读取的数据
    io.wb_memory_read_data := MuxLookup( 
      io.funct3, // 根据功能码选择读取的数据
      0.U, // 默认读取0
      IndexedSeq(
        InstructionsTypeL.lb -> MuxLookup(
          mem_address_index,
          Cat(Fill(24, data(31)), data(31, 24)),
          IndexedSeq(
            0.U -> Cat(Fill(24, data(7)), data(7, 0)),
            1.U -> Cat(Fill(24, data(15)), data(15, 8)),
            2.U -> Cat(Fill(24, data(23)), data(23, 16))
          )
        ),
        InstructionsTypeL.lbu -> MuxLookup(
          mem_address_index,
          Cat(Fill(24, 0.U), data(31, 24)),
          IndexedSeq(
            0.U -> Cat(Fill(24, 0.U), data(7, 0)),
            1.U -> Cat(Fill(24, 0.U), data(15, 8)),
            2.U -> Cat(Fill(24, 0.U), data(23, 16))
          )
        ),
        InstructionsTypeL.lh -> Mux(
          mem_address_index === 0.U,
          Cat(Fill(16, data(15)), data(15, 0)),
          Cat(Fill(16, data(31)), data(31, 16))

        ),
        InstructionsTypeL.lhu -> Mux(
          mem_address_index === 0.U,
          Cat(Fill(16, 0.U), data(15, 0)),
          Cat(Fill(16, 0.U), data(31, 16))
        ),
        InstructionsTypeL.lw -> data
      )
    )
  }.elsewhen(io.memory_write_enable) { // 当使能内存写时，向内存中写入数据
    io.memory_bundle.write_data := io.reg2_data
    io.memory_bundle.write_enable := true.B
    io.memory_bundle.write_strobe := VecInit(Seq.fill(Parameters.WordSize)(false.B))
    when(io.funct3 === InstructionsTypeS.sb) {
      io.memory_bundle.write_strobe(mem_address_index) := true.B
      io.memory_bundle.write_data := io.reg2_data(Parameters.ByteBits, 0) << (mem_address_index << log2Up(Parameters.ByteBits).U)
    }.elsewhen(io.funct3 === InstructionsTypeS.sh) {
      when(mem_address_index === 0.U) {
        for (i <- 0 until Parameters.WordSize / 2) {
          io.memory_bundle.write_strobe(i) := true.B
        }
        io.memory_bundle.write_data := io.reg2_data(Parameters.WordSize / 2 * Parameters.ByteBits, 0)
      }.otherwise {
        for (i <- Parameters.WordSize / 2 until Parameters.WordSize) {
          io.memory_bundle.write_strobe(i) := true.B
        }
        io.memory_bundle.write_data := io.reg2_data(Parameters.WordSize / 2 * Parameters.ByteBits, 0) << (Parameters
          .WordSize / 2 * Parameters.ByteBits)
      }
    }.elsewhen(io.funct3 === InstructionsTypeS.sw) {
      for (i <- 0 until Parameters.WordSize) {
        io.memory_bundle.write_strobe(i) := true.B
      }
    }
  }
}