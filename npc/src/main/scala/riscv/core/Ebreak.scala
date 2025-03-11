package riscv.core

import chisel3._
import chisel3.util._
import riscv.Parameters

class Ebreak extends BlackBox with HasBlackBoxInline {
  val io = IO(new Bundle {
    val clock = Input(Clock())
    val instruction = Input(UInt(Parameters.InstructionWidth))
  })

  // 内联 Verilog 代码
  setInline("Ebreak.sv",
    s"""
       |module Ebreak (
       |    input  clock,
       |    input [31:0] instruction
       |);
       | import "DPI-C" function void set_npctrap(int i);
       | always @(posedge clock) begin
       |    if (instruction == 32'b00000000000100000000000001110011) begin
       |       set_npctrap(1);
       |    end
       | end
       |endmodule
     """.stripMargin)
}