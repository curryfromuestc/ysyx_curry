package rv32

import chisel3._
import chisel3.util._
import Parameters._
class Ebreak extends BlackBox with HasBlackBoxInline {
  val io = IO(new Bundle {
    val clock = Input(Clock())
    val instruction = Input(UInt(WORD_LEN.W))
  })

  // 内联 Verilog 代码
  setInline("Ebreak.sv",
    s"""
       |module Ebreak (
       |    input  clock,
       |    input [31:0] instruction
       |);
       | import "DPI-C" function void npc_trap(int i);
       | always @(posedge clock) begin
       |    if (instruction == 32'b00000000000100000000000001110011) begin
       |       npc_trap(1);
       |    end
       | end
       |endmodule
     """.stripMargin)
}