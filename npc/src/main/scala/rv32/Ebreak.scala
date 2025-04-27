package rv32

import chisel3._
import chisel3.util._
import chisel3.experimental._
import Parameters._

class Ebreak extends BlackBox with HasBlackBoxInline {
  val io = IO(new Bundle {
    val instruction = Input(UInt(WORD_LEN.W))
  })

  setInline("Ebreak.v",
    """module Ebreak (
    |    input [31:0] instruction
    |);
    |    import "DPI-C" function void halt();
    |    always @(*) begin
    |        if (instruction == 32'b00000000000100000000000001110011) begin
    |            halt();
    |        end
    |    end
    |endmodule""".stripMargin)
}