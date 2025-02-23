package riscv.core

import chisel3._
// import chisel3.experimental.ChiselEnum
// Warn: type ChiselEnum in package experimental is deprecated (since Chisel 3.5): This type has moved to chisel3
// In contrast with Chisel.util.Enum, ChiselEnum are subclasses of Data, which means that they can be used to define fields in Bundles, including in IOs.
import chisel3.util._
import riscv.Parameters

object ALUFunctions extends ChiselEnum {
  val zero, add, sub, sll, slt, xor, or, and, srl, sra, sltu = Value
}


class ALU extends Module {
  val io = IO(new Bundle {
    val func = Input(ALUFunctions()) // ALU功能

    val op1 = Input(UInt(Parameters.DataWidth)) // 操作数1
    val op2 = Input(UInt(Parameters.DataWidth)) // 操作数2

    val result = Output(UInt(Parameters.DataWidth)) // 计算结果
  })

  io.result := 0.U
  switch(io.func) {
    is(ALUFunctions.add) {
      io.result := io.op1 + io.op2
    }
    is(ALUFunctions.sub) {
      io.result := io.op1 - io.op2
    }
    is(ALUFunctions.sll) {
      io.result := io.op1 << io.op2(4, 0)
    }
    is(ALUFunctions.slt) {
      io.result := io.op1.asSInt < io.op2.asSInt
    }
    is(ALUFunctions.xor) {
      io.result := io.op1 ^ io.op2
    }
    is(ALUFunctions.or) {
      io.result := io.op1 | io.op2
    }
    is(ALUFunctions.and) {
      io.result := io.op1 & io.op2
    }
    is(ALUFunctions.srl) {
      io.result := io.op1 >> io.op2(4, 0)
    }
    is(ALUFunctions.sra) {
      io.result := (io.op1.asSInt >> io.op2(4, 0)).asUInt
    }
    is(ALUFunctions.sltu) {
      io.result := io.op1 < io.op2
    }
  }

}