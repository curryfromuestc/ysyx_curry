package riscv.core

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec
import riscv.TestAnnotations

import riscv.core.{InstructionDecode}

class InstructionDecodeTest extends AnyFlatSpec with ChiselScalatestTester {
    behavior of "InstructionDecoder of Single Cycle CPU"
    it should "produce correct control signal" in {
        test(new InstructionDecode).withAnnotations(TestAnnotations.annos) { c =>
            c.io.instruction.poke(0x00a02223L.U) //S-type:  sw x10, 4(x0)
            c.io.ex_aluop1_source.expect(ALUOp1Source.Register) // 操作数1来自寄存器
            c.io.ex_aluop2_source.expect(ALUOp2Source.Immediate) // 操作数2来自立即数
            c.io.regs_reg1_read_address.expect(0.U) // 读取寄存器1的地址为0
            c.io.regs_reg2_read_address.expect(10.U) // 读取寄存器2的地址为10
            c.clock.step()

            c.io.instruction.poke(0x000022b7L.U) //U-type, lui x5, 2
            c.io.regs_reg1_read_address.expect(0.U) // 读取寄存器1的地址为0
            c.io.ex_aluop1_source.expect(ALUOp1Source.Register) // 操作数1来自寄存器
            c.io.ex_aluop2_source.expect(ALUOp2Source.Immediate) // 操作数2来自立即数
            c.clock.step()

            c.io.instruction.poke(0x002081b3L.U) //R-type，add x3, x1, x2 
            c.io.ex_aluop1_source.expect(ALUOp1Source.Register) // 操作数1来自寄存器
            c.io.ex_aluop2_source.expect(ALUOp2Source.Register) // 操作数2来自寄存器
            c.clock.step()

            // @TODO: 补充I-type，J-type, B-type的测试
            c.io.instruction.poke(0x064000efL.U) //J-type, jal x1, 100
            c.io.ex_aluop1_source.expect(ALUOp1Source.InstructionAddress) // 操作数1来自PC
            c.io.ex_aluop2_source.expect(ALUOp2Source.Immediate) // 操作数2来自立即数
            c.clock.step()

            c.io.instruction.poke(0x06410067L.U) //I-type, jalr  x0, 100(x2)
            c.io.ex_aluop1_source.expect(ALUOp1Source.Register) // 操作数1来自寄存器
            c.io.ex_aluop2_source.expect(ALUOp2Source.Immediate) // 操作数2来自立即数
            c.clock.step()

            // c.io.instruction.poke(0x06200263L.U) //B-type, beq x0, x2, 100
            // c.io.ex_aluop1_source.expect(ALUOp1Source.Register) // 操作数1来自寄存器
            // c.io.ex_aluop2_source.expect(ALUOp2Source.Register) // 操作数2来自寄存器
            // c.clock.step()

        }
    }
}