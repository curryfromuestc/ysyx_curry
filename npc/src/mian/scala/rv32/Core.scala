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

class FetchStage{
    val pc = RegInit(START_ADDR)
}
class DecodeStage{
}
class ExecuteStage{
}
