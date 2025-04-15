import chisel3._
import chisel3.util._

class PCBundle extends Bundle {
    val pc = Output(UInt(32.W))
    val pc_plus4 = Output(UInt(32.W))
    val pc_plus8 = Output(UInt(32.W))
    val pc_plus12 = Output(UInt(32.W)) 
}