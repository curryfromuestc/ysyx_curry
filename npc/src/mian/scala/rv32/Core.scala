package rv32

import chisel3._
import chisel3.util._
import Parameters._

//         +--+          +--+          +--+          +--+
// +----+  |  |  +----+  |  |  +----+  |  |  +----+  |  |  +----+
// |    |  |  |  |    |  |  |  |    |  |  |  |    |  |  |  |    |
// | IF |->|  |->| ID |->|  |->| EX |->|  |->| MEM|->|  |->| WB |
// |    |  |  |  |    |  |  |  |    |  |  |  |    |  |  |  |    |
// +----+  |  |  +----+  |  |  +----+  |  |  +----+  |  |  +----+
//         +--+          +--+          +--+          +--+
//        IF/ID         ID/EX         EX/MEM        MEM/WB
//      registers     registers     registers     registers

class FetchStageBundle extends Bundle {
    val exeBrFlag = Input(Bool())
    val exeBrTarget = Input(UInt(WORD_LEN.W))
    val exeJmpFlag = Input(Bool())
    val exeAluOut = Input(UInt(WORD_LEN.W))
    val stallFlag = Input(Bool())
}
class DecodeStageBundle extends Bundle {
}
class ExecuteStageBundle extends Bundle {
}
