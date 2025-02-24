/**
package peripheral

import chisel3._
import chisel3.util._
import riscv.Parameters

class RAMBundle extends Bundle {
    val address = Input(UInt(Paramters.AddrWidth))
    val read_data = Output(UInt(Parameters.DataWidth))
    val write_data = Input(UInt(Paramters.DataWidth))
    val write_enable = Input(Bool())
    val write_strobe = Input(Vec(Parameters.WordSize, Bool())) // strobe is a mask, 是一个掩码
}

class Memory(capacity: Int) extends Module {
    val io = IO(new Bundle {
        val bundle = new RAMBundle // 当要读写内存中的内容为数据，IO接口使用RAMBundle
        // 当用读写内存中的内容为指令时，IO接口使用下面的接口
        val instruction_address = Input(UInt(Parameters.AddrWidth)) // 指令地址
        val instruction = Output(UInt(Parameters.DataWidth)) // 指令
        val debug_read_address = Input(UInt(Parameters.AddrWidth))
        val debug_read_data = Output(UInt(Parameters.DataWidth))
    })
    // SyncReadMem是一个同步读内存, 第一个参数是容量, 第二个参数是数据类型
    val mem = SyncReadMem(capacity, Vec(Parameters.WordSize, UInt(Parameters.ByteWidth)))
    when(io.bundle.write_enable) {
        // 定义write_data_vec为一个Vec, 它的每个元素是一个UInt(Parameters.ByteWidth)类型的数据
        val write_data_vec = Wire(Vec(Parameters.WordSize, UInt(Parameters.ByteWidth)))
        for (i <- 0 until Parameters.WordSize) {
            // 填充write_data_vec, 通过循环将write_data的每个字节分别赋值给write_data_vec
            write_data_vec(i) := io.bundle.write_data((i + 1) * Parameters.ByteBits - 1, i * Parameters.ByteBits)
        }
        // mem.write的第一个参数是地址, 第二个参数是数据, 第三个参数是掩码
        mem.write((io.bundle.address >> 2.U).asUInt, write_data_vec, io.bundle.write_strobe)
    }
    io.bundle.read_data := mem.read((io.bundle.address >> 2.U).asUInt, true.B).asUInt
    io.debug_read_data := mem.read((io.debug_read_address >> 2.U).asUInt, true.B).asUInt
    io.instruction := mem.read((io.instruction_address >> 2.U).asUInt, true.B).asUInt
}
**/


package peripheral

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec
import riscv.TestAnnotations
import riscv.Parameters

import peripheral.Memory

// 编写Memory的测试代码
class MemoryTest extends AnyFlatSpec with ChiselScalatestTester {
    behavior of "Memory"
    it should "read the write data" in {
        test(new Memory(1024)).withAnnotations(TestAnnotations.annos) { c =>
            c.io.bundle.address.poke(0x123123.U) // 写入地址
            c.io.bundle.write_data.poke(0x12345678.U) // 写入数据
            c.io.bundle.write_enable.poke(true.B) // 写使能
            //c.io.bundle.write_strobe.poke(VecInit(Seq.fill(Parameters.WordSize)(true.B))) // 写掩码
            // 不能使用上面的写掩码, 因为VecInit(Seq.fill(Parameters.WordSize)(true.B))是一个Vec[Bool], 而write_strobe是一个Vec[Bool]
            // 但是Vec[Bool]和Vec[Bool]是不同的类型, 所以不能直接赋值
            // 可以使用下面的方法
            for (i <- 0 until Parameters.WordSize) {
                c.io.bundle.write_strobe(i).poke(true.B)
            }
            c.clock.step(1)
            c.io.bundle.address.poke(0x123123.U) // 写入地址
            c.io.bundle.read_data.expect(0x12345678.U)
        }
    }
    it should "read the written instruction" in {
        test(new Memory(1024)).withAnnotations(TestAnnotations.annos) { c =>
            timescope {
                c.io.bundle.address.poke(0x123123.U)
                c.io.bundle.write_data.poke(0x00a02223L.U) //sw x10, 4(x0)
                c.io.bundle.write_enable.poke(true.B)
                for (i <- 0 until Parameters.WordSize) {
                    c.io.bundle.write_strobe(i).poke(true.B)
                }
                c.clock.step(1)
                c.io.bundle.read_data.expect(0x00a02223L.U)
            }
            timescope {
                c.io.instruction_address.poke(0x123123.U)
                c.clock.step(1)
                c.io.instruction.expect(0x00a02223L.U)
            }
        }
    }
}