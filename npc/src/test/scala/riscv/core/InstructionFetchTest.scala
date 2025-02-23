package riscv.core

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec
import riscv.TestAnnotations
import riscv.Parameters
import riscv.core.{InstructionFetch}

import scala.math.pow
import scala.util.Random

class InstructionFetchTest extends AnyFlatSpec with ChiselScalatestTester{
  behavior of "InstructionFetch of Single Cycle CPU"
  it should "fetch instruction" in {
    test(new InstructionFetch).withAnnotations(TestAnnotations.annos) { c =>
      val entry = BigInt("80000000",16) // 程序入口地址
      var pre = entry // 保存上一条指令的地址
      var cur = pre   // 保存当前指令的地址
      var x = 0       // 用于计数
      for (x <- 0 to 100) {
        // 随机生成指令, nextInt(3)生成0或1或2
        Random.nextInt(3) match {
          case 0 => // no jump
            c.io.instruction_valid.poke(true.B) // 使能指令有效信号
            cur = pre + 4 // 顺序执行，PC += 4
            c.io.jump_flag_id.poke(false.B) // 禁用跳转
            c.clock.step()// 时钟步进
            c.io.instruction_address.expect(cur) // 检查PC的值, 希望PC的值为cur
            pre = pre + 4
          case 1 => // jump
            c.io.instruction_valid.poke(true.B) // 使能指令有效信号
            c.io.jump_flag_id.poke(true.B) // 使能跳转
            c.io.jump_address_id.poke(BigInt("80000000",16)) // 跳转到目标地址，这里假设目标地址为0x0000_1200
            c.clock.step()                  //  时钟步进
            c.io.instruction_address.expect(BigInt("80000000",16)) // 检查PC的值, 希望PC的值为0x0000_1200
            pre = BigInt("80000000",16)
          case 2 => // invalid
            c.io.instruction_valid.poke(false.B) // 禁用指令有效信号
            c.clock.step() // 时钟步进
            c.io.instruction_address.expect(pre) // 检查PC的值, 希望PC的值为pre
            c.io.instruction.expect(0x0000_0013.U) // 检查输出的指令, 希望输出NOP指令
        }
      }

      }
    }
}