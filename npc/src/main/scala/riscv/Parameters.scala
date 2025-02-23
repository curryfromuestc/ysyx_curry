package riscv

import chisel3._
import chisel3.util._

object Parameters {
    val AddrBits = 32 // 地址总线位宽
    val AddrWidth = AddrBits.W // 地址总线宽度

    val ByteBits = 8
    val ByteWidth = ByteBits.W

    val DataBits = 32 // 数据总线位宽
    val DataWidth = DataBits.W // 数据总线宽度
    
    val EntryAddress = BigInt("80000000",16).U(Parameters.AddrWidth) // 程序入口地址

    val InstructionBits = 32
    val InstructionWidth = InstructionBits.W

    val PhysicalRegisters = 32
    val PhysicalRegisterAddrBits = log2Up(PhysicalRegisters)
    val PhysicalRegisterAddrWidth = PhysicalRegisterAddrBits.W

    val WordSize = Math.ceil(DataBits / ByteBits).toInt
}