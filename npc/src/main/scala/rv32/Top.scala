package rv32

import chisel3._
import chisel3.util._
import Parameters._
import _root_.circt.stage.ChiselStage

class Top extends Module{
    val core = Module(new Core)
    val mem = Module(new Memory)

    core.io.imem <> mem.io.imem
    core.io.dmem <> mem.io.dmem
}

object Top extends App {
  ChiselStage.emitSystemVerilogFile(
    new Top,
    firtoolOpts = Array("-disable-all-randomization", "-strip-debug-info"),
    args = Array("--target-dir", "vsrc")
  )
}
