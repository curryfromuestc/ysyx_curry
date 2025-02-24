package riscv.core

import chisel3._
import chisel3.util.{Cat, MuxLookup}

import riscv.Parameters

class Execute extends Module {
  val io = IO(new Bundle {
    val instruction = Input(UInt(Parameters.InstructionWidth)) // 指令
    val instruction_address = Input(UInt(Parameters.AddrWidth)) // 指令地址
    val reg1_data = Input(UInt(Parameters.DataWidth)) // 寄存器1的数据
    val reg2_data = Input(UInt(Parameters.DataWidth)) // 寄存器2的数据
    val immediate = Input(UInt(Parameters.DataWidth)) // 立即数
    val aluop1_source = Input(UInt(1.W)) // 操作数1的来源
    val aluop2_source = Input(UInt(1.W)) // 操作数2的来源

    val mem_alu_result = Output(UInt(Parameters.DataWidth)) // 计算结果
    val if_jump_flag = Output(Bool()) // 是否跳转
    val if_jump_address = Output(UInt(Parameters.DataWidth)) // 跳转地址
  })

  val opcode = io.instruction(6, 0)
  val funct3 = io.instruction(14, 12) // 3位功能码
  val funct7 = io.instruction(31, 25) // 7位功能码
  val rd = io.instruction(11, 7)  // 目标寄存器地址
  val uimm = io.instruction(19, 15) // 无符号立即数

  val alu = Module(new ALU) // ALU模块
  val alu_ctrl = Module(new ALUControl) // ALU控制模块

  alu_ctrl.io.opcode := opcode
  alu_ctrl.io.funct3 := funct3
  alu_ctrl.io.funct7 := funct7

  // @TODO: 把alu_ctrl的输出接到alu的输入
  alu.io.func := alu_ctrl.io.alu_funct // ALU功能
  alu.io.op1 := MuxLookup(
    io.aluop1_source,
    0.U,
    IndexedSeq(
      ALUOp1Source.Register -> io.reg1_data,
      ALUOp1Source.InstructionAddress -> io.instruction_address
    )
  ) // 操作数1
  alu.io.op2 := MuxLookup(
    io.aluop2_source,
    0.U,
    IndexedSeq(
      ALUOp2Source.Register -> io.reg2_data,
      ALUOp2Source.Immediate -> io.immediate
    )
  ) // 操作数2
  io.mem_alu_result := alu.io.result // 计算结果
  io.if_jump_flag := opcode === Instructions.jal ||
    (opcode === Instructions.jalr) ||
    (opcode === InstructionTypes.B) && MuxLookup(
      funct3,
      false.B,
      IndexedSeq(
        InstructionsTypeB.beq -> (io.reg1_data === io.reg2_data),
        InstructionsTypeB.bne -> (io.reg1_data =/= io.reg2_data),
        InstructionsTypeB.blt -> (io.reg1_data.asSInt < io.reg2_data.asSInt),
        InstructionsTypeB.bge -> (io.reg1_data.asSInt >= io.reg2_data.asSInt),
        InstructionsTypeB.bltu -> (io.reg1_data.asUInt < io.reg2_data.asUInt),
        InstructionsTypeB.bgeu -> (io.reg1_data.asUInt >= io.reg2_data.asUInt)
      )
    ) 
  io.if_jump_address := io.immediate + Mux(opcode === Instructions.jalr, io.reg1_data, io.instruction_address)
}