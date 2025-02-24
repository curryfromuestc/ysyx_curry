package riscv.core

import chisel3._
import chisel3.util._
import riscv.Parameters

object InstructionTypes {
    val L = "b000_0011".U(7.W)
    val I = "b001_0011".U(7.W)
    val S = "b010_0011".U(7.W)
    val B = "b110_0011".U(7.W)
    val RM = "b011_0011".U(7.W)
}

object Instructions {
    val lui = "b0110111".U(7.W)
    val nop = "b0000000".U(7.W)
    val jal = "b1101111".U(7.W)
    val jalr = "b1100111".U(7.W)
    val auipc = "b0010111".U(7.W)
    val csr = "b1110011".U(7.W)
    val fence = "b0001111".U(7.W)
}

object InstructionsTypeL {
    val lb = "b000".U(3.W)
    val lh = "b001".U(3.W)
    val lw = "b010".U(3.W)
    val lbu = "b100".U(3.W)
    val lhu = "b101".U(3.W)
}

object InstructionsTypeI {
  val addi = 0.U
  val slli = 1.U
  val slti = 2.U
  val sltiu = 3.U
  val xori = 4.U
  val sri = 5.U
  val ori = 6.U
  val andi = 7.U
}

object InstructionsTypeS {
  val sb = "b000".U
  val sh = "b001".U
  val sw = "b010".U
}

object InstructionsTypeR {
  val add_sub = 0.U
  val sll = 1.U
  val slt = 2.U
  val sltu = 3.U
  val xor = 4.U
  val sr = 5.U
  val or = 6.U
  val and = 7.U
}

object InstructionsTypeM {
  val mul = 0.U
  val mulh = 1.U
  val mulhsu = 2.U
  val mulhum = 3.U
  val div = 4.U
  val divu = 5.U
  val rem = 6.U
  val remu = 7.U
}

object InstructionsTypeB {
  val beq = "b000".U
  val bne = "b001".U
  val blt = "b100".U
  val bge = "b101".U
  val bltu = "b110".U
  val bgeu = "b111".U
}

object InstructionsTypeCSR {
  val csrrw = "b001".U
  val csrrs = "b010".U
  val csrrc = "b011".U
  val csrrwi = "b101".U
  val csrrsi = "b110".U
  val csrrci = "b111".U
}

object InstructionsNop {
  val nop = 0x00000013L.U(Parameters.DataWidth)
}

object InstructionsRet {
  val mret = 0x30200073L.U(Parameters.DataWidth)
  val ret = 0x00008067L.U(Parameters.DataWidth)
}

object InstructionsEnv {
  val ecall = 0x00000073L.U(Parameters.DataWidth)
  val ebreak = 0x00100073L.U(Parameters.DataWidth)
}

object ALUOp1Source {
  val Register = 0.U(1.W)
  val InstructionAddress = 1.U(1.W)
}

object ALUOp2Source {
  val Register = 0.U(1.W)
  val Immediate = 1.U(1.W)
}

// 写回阶段的数据来源
object RegWriteSource {
  val ALUResult = 0.U(2.W) // ALU计算结果, 0.U(2.W)表示二进制的00
  val Memory = 1.U(2.W) // 从内存中读取的数据, 1.U(2.W)表示二进制的01
  //val CSR = 2.U(2.W)
  val NextInstructionAddress = 3.U(2.W) // 下一条指令的地址，3.U(2.W)表示二进制的11
}

class InstructionDecode extends Module {
    val io = IO(new Bundle{
        val instruction = Input(UInt(Parameters.InstructionWidth))
        val regs_reg1_read_address = Output(UInt(Parameters.PhysicalRegisterAddrWidth)) // 从寄存器堆读取的第一个寄存器的地址
        val regs_reg2_read_address = Output(UInt(Parameters.PhysicalRegisterAddrWidth)) // 从寄存器堆读取的第二个寄存器的地址
        val ex_immediate = Output(UInt(Parameters.DataWidth))  // 立即数
        val ex_aluop1_source = Output(UInt(1.W))  // ALU第一个操作数来源
        val ex_aluop2_source = Output(UInt(1.W))  // ALU第二个操作数来源
        val memory_read_enable = Output(Bool())   // 是否使能内存读
        val memory_write_enable = Output(Bool())  // 是否使能内存写
        val wb_reg_write_source = Output(UInt(2.W))  // 寄存器写入来源
        val reg_write_enable = Output(Bool())  // 是否使能寄存器写
        val reg_write_address = Output(UInt(Parameters.PhysicalRegisterAddrWidth)) // 寄存器写入地址
    })
    val opcode = io.instruction(6, 0) // 操作码
    val funct3 = io.instruction(14, 12) // 功能码
    val funct7 = io.instruction(31, 25) // 功能码
    val rd = io.instruction(11, 7)  // 目标寄存器地址
    val rs1 = io.instruction(19, 15) // 源寄存器1地址
    val rs2 = io.instruction(24, 20)  // 源寄存器2地址

    io.regs_reg1_read_address := Mux(opcode === Instructions.lui, 0.U(Parameters.PhysicalRegisterAddrWidth), rs1) // 源寄存器1地址, lui指令的源寄存器1地址为0, 其余指令的源寄存器1地址为rs1
    io.regs_reg2_read_address := rs2 // 源寄存器2地址
    val immediate = MuxLookup( // MuxLookup是一个多路选择器，第一个参数是选择器，第二个参数是默认值，第三个参数是一个元组，元组的第一个元素是选择器的值，第二个元素是选择器的值对应的结果
        opcode, // 选择器, 即操作码
        Cat(Fill(20, io.instruction(31)), io.instruction(31, 20)), 
        // 默认值, 即当选择器的值不在元组的第三个参数中时, 返回的值
        IndexedSeq(
            InstructionTypes.I -> Cat(Fill(21, io.instruction(31)), io.instruction(30, 20)), 
            // I类指令, 即立即数指令, imm[31:20] - rs1[19:15] - funct3[14:12] - rd[11:7] - opcode[6:0] 
            InstructionTypes.L -> Cat(Fill(21, io.instruction(31)), io.instruction(30, 20)), 
            // 加载指令, 和I类指令一样
            Instructions.jalr -> Cat(Fill(21, io.instruction(31)), io.instruction(30, 20)),  
            // jalr指令, 和I类指令一样
            InstructionTypes.S -> Cat(Fill(21, io.instruction(31)), io.instruction(30, 25), io.instruction(11, 7)), 
            // S类指令, 即存储指令, imm[31:25] - rs2[24:20] - rs1[19:15] - funct3[14:12] - imm[11:7] - opcode[6:0]
            InstructionTypes.B -> Cat(Fill(20, io.instruction(31)), io.instruction(7), io.instruction(30, 25), io.instruction(11, 8), 0.U(1.W)), 
            // B类指令, 即分支指令, imm[31] - imm[7] - imm[30:25] - rs2[24:20] - rs1[19:15] - funct3[14:12] - imm[11:8] - 0
            Instructions.lui -> Cat(io.instruction(31, 12), 0.U(12.W)),
            // lui, U类指令, 即上界立即数指令, imm[31:12] - rd[11:7] - opcode[6:0]
            Instructions.auipc -> Cat(io.instruction(31, 12), 0.U(12.W)),
            // auipc指令, 将31到12位的值复制到0到19位, 将0拼接到20到31位
            Instructions.jal -> Cat(Fill(12, io.instruction(31)), io.instruction(19, 12), io.instruction(20), io.instruction(30, 21), 0.U(1.W))
            // jal指令,  imm[31] - imm[19:12] - imm[20] - imm[30:21] - 0
        )
    )
    io.ex_immediate := immediate 
    io.ex_aluop1_source := Mux(
        opcode === Instructions.auipc || opcode === InstructionTypes.B || opcode === Instructions.jal,
        ALUOp1Source.InstructionAddress,
        ALUOp1Source.Register
    )// ALU第一个操作数来源, 如果是auipc指令, 分支指令或jal指令, 则为指令地址, 否则为寄存器堆的值
    // @TODO: 补充为ex_aluop2_source, memory_read_enable, memory_write_enable, wb_reg_write_source四个控制信号赋值的代码
    io.ex_aluop2_source := Mux(
        opcode === InstructionTypes.S ||  opcode === InstructionTypes.I || opcode === InstructionTypes.L || opcode === Instructions.jalr || opcode === Instructions.auipc || opcode === Instructions.lui || opcode === Instructions.jal,
        ALUOp2Source.Immediate,
        ALUOp2Source.Register
    ) // ALU第二个操作数来源, 如果是I类指令, L类指令, jalr指令, auipc指令, lui指令或jal指令, 则为立即数, 否则为寄存器堆的值
    io.memory_read_enable := (opcode === InstructionTypes.L) // 是否使能内存读, 如果是L类指令, 则使能内存读
    io.memory_write_enable := (opcode === InstructionTypes.S) // 是否使能内存写, 如果是S类指令, 则使能内存写
    io.wb_reg_write_source := Mux(
        opcode === InstructionTypes.RM || opcode === InstructionTypes.I || opcode === InstructionTypes.L || opcode === Instructions.auipc || opcode === Instructions.lui || opcode === Instructions.jal || opcode === Instructions.jalr,
        RegWriteSource.ALUResult,
        RegWriteSource.Memory
    ) // 寄存器写入来源, 如果是R类指令, I类指令, L类指令, U类指令, auipc指令, jal指令或jalr指令, 则为ALU的结果, 否则为内存的值

    io.reg_write_enable := (opcode === InstructionTypes.RM) || (opcode === InstructionTypes.I) ||
    (opcode === InstructionTypes.L) || (opcode === Instructions.auipc) || (opcode === Instructions.lui) ||
    (opcode === Instructions.jal) || (opcode === Instructions.jalr) // 是否使能寄存器写, 如果是R类指令, I类指令, L类指令, U类指令, auipc指令, jal指令或jalr指令, 则使能寄存器写
    
    io.reg_write_address := io.instruction(11, 7) // 寄存器写入地址, 即目标寄存器地址
}