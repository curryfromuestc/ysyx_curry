package rv32i

import chisel3._
import chisel3.simulator.EphemeralSimulator._
import org.scalatest.flatspec.AnyFlatSpec

import config.Configs._

class PCRegTest extends AnyFlatSpec {
    behavior of "PCReg"
    it should "do something" in {
        simulate(new PCReg) { dut =>
            dut.io.ctrlJump.poke(true.B)
            dut.io.ctrlBranch.poke(false.B)
            dut.io.resultBranch.poke(false.B)
            dut.io.addrTarget.poke(BigInt("80000004", 16).U)
            dut.clock.step()
            dut.io.addrOut.expect(BigInt("80000004", 16).U)
            println("Test 1 passed")
        }
    }
}
