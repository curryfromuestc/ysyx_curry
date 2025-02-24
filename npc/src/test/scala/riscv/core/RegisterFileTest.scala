package riscv.core

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec
import riscv.TestAnnotations
import riscv.core.RegisterFile

class RegisterFileTest extends AnyFlatSpec with ChiselScalatestTester {
    behavior of "RegisterFile"
    it should "read the written content" in {
        // 测试寄存器文件的读写功能, 先写入一个值，然后读出来
        test(new RegisterFile).withAnnotations(TestAnnotations.annos){ c =>
            timescope{
                // timescope 规定了poke激励的作用范围，被激励的端口会在timescope之后回到原来的状态
                // timescope 的写法的好处是，简化了代码，不需要在每个poke之后都写一遍poke的反激励
                c.io.write_enable.poke(true.B) // 激励写使能信号为1
                c.io.write_address.poke(1.U) // 激励写地址为1
                c.io.write_data.poke(0xDEADBEEFL.U) // 激励写数据为0xDEADBEEF
                c.clock.step() // 时钟步进一拍
            }
            // timescope之后，写使能信号为0，写地址为0，写数据为0
            c.io.read_address1.poke(1.U) // 激励读地址为1
            c.io.read_data1.expect(0xDEADBEEFL.U) // 期望读数据为0xDEADBEEF
        }
    }
    it should "x0 always be zero" in {
        // 测试x0寄存器是否总是0
        test(new RegisterFile).withAnnotations(TestAnnotations.annos){ c =>
           timescope {
                c.io.write_enable.poke(true.B) // 激励写使能信号为1
                c.io.write_address.poke(0.U)  // 激励写地址为0
                c.io.write_data.poke(0xDEADBEEFL.U) // 激励写数据为0xDEADBEEF, 但是写地址为0，所以不会写入
                c.clock.step()  // 时钟步进一拍
           }
           c.io.read_address1.poke(0.U) // 激励读地址为0
           c.io.read_data1.expect(0.U)  // 期望读数据为0
        }
    }
    it should "read the writing content" in {
        test(new RegisterFile).withAnnotations(TestAnnotations.annos){ c =>
            timescope {
                c.io.read_address1.poke(2.U) // 激励读地址为2
                c.io.read_data1.expect(0.U) // 期望读数据为0，因为0是初始化的值
                c.io.write_enable.poke(true.B) // 激励写使能信号为1
                c.io.write_address.poke(2.U) // 激励写地址为2
                c.io.write_data.poke(0xDEADBEEFL.U) // 激励写数据为0xDEADBEEF
                c.clock.step()
                c.io.read_address1.poke(2.U) // 激励读地址为2
                c.io.read_data1.expect(0xDEADBEEFL.U) // 期望读数据为0xDEADBEEF
                c.clock.step()
            }
            c.io.read_address1.poke(2.U) // 激励读地址为2
            c.io.read_data1.expect(0xDEADBEEFL.U) // 期望读数据为0xDEADBEEF
        }
    }
    it should "read the written content in debug mode: 调试模式" in {
        test(new RegisterFile).withAnnotations(TestAnnotations.annos){ c =>
            timescope {
                c.io.write_enable.poke(true.B) // 激励写使能信号为1
                c.io.write_address.poke(1.U)  // 激励写地址为1
                c.io.write_data.poke(0xDEADBEEFL.U) // 激励写数据为0xDEADBEEF
                c.clock.step() // 时钟步进一拍
            }
            c.io.debug_read_address.poke(1.U) // 激励调试读地址为1
            c.io.debug_read_data.expect(0xDEADBEEFL.U) // 期望调试读数据为0xDEADBEEF
        }
    }
}