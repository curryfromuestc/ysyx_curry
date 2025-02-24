package riscv.core
import chisel3._
import riscv.Parameters

object Registes extends Enumeration {
  type Register = Value
  val   zero,
        ra, sp, gp, tp,
        t0, t1, t2, fp,
        s1,
        a0, a1, a2, a3, a4, a5, a6, a7,
        s2, s3, s4, s5, s6, s7, s8, s9, s10, s11,
        t3, t4, t5, t6 = Value
}
class RegisterFile extends Module{
    val io = IO(new Bundle{
        val write_enable = Input(Bool())
        val write_address = Input(UInt(Parameters.PhysicalRegisterAddrWidth))
        val write_data = Input(UInt(Parameters.DataWidth))
        val read_address1 = Input(UInt(Parameters.PhysicalRegisterAddrWidth))
        val read_address2 = Input(UInt(Parameters.PhysicalRegisterAddrWidth))
        val read_data1 = Output(UInt(Parameters.DataWidth))
        val read_data2 = Output(UInt(Parameters.DataWidth))
        // debug是在调试时，用户通过调试器查看寄存器的值
        val debug_read_address = Input(UInt(Parameters.PhysicalRegisterAddrWidth))
        val debug_read_data = Output(UInt(Parameters.DataWidth))
    })
    val registers = RegInit(VecInit(Seq.fill(Parameters.PhysicalRegisters)(0.U(Parameters.DataWidth))))
    
    when(!reset.asUInt.asBool){ // 当reset信号为0时，表示复位
        when(io.write_enable && io.write_address =/= 0.U){ // 运算符=/=是不等于
            // 当写使能信号为1且写地址不为0时, 将写数据写入到寄存器中
            registers(io.write_address) := io.write_data
        }
    }
    io.read_data1 := Mux(
        io.read_address1 === 0.U,
        0.U,
        registers(io.read_address1)
    )
    io.read_data2 := Mux(
        io.read_address2 === 0.U,
        0.U,
        registers(io.read_address2)
    )
    io.debug_read_data := Mux(
        io.debug_read_address === 0.U,
        0.U,
        registers(io.debug_read_address)
    )
}