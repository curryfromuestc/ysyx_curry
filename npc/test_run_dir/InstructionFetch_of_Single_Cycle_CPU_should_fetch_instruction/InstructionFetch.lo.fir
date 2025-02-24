FIRRTL version 1.2.0
circuit InstructionFetch :
  module InstructionFetch :
    input clock : Clock
    input reset : UInt<1>
    input io_jump_flag_id : UInt<1> @[src/main/scala/riscv/core/InstructionFetch.scala 11:16]
    input io_jump_address_id : UInt<32> @[src/main/scala/riscv/core/InstructionFetch.scala 11:16]
    input io_instruction_read_data : UInt<32> @[src/main/scala/riscv/core/InstructionFetch.scala 11:16]
    input io_instruction_valid : UInt<1> @[src/main/scala/riscv/core/InstructionFetch.scala 11:16]
    output io_instruction_address : UInt<32> @[src/main/scala/riscv/core/InstructionFetch.scala 11:16]
    output io_instruction : UInt<32> @[src/main/scala/riscv/core/InstructionFetch.scala 11:16]

    reg pc : UInt<32>, clock with :
      reset => (UInt<1>("h0"), pc) @[src/main/scala/riscv/core/InstructionFetch.scala 22:21]
    node _pc_T = add(pc, UInt<3>("h4")) @[src/main/scala/riscv/core/InstructionFetch.scala 34:22]
    node _pc_T_1 = tail(_pc_T, 1) @[src/main/scala/riscv/core/InstructionFetch.scala 34:22]
    node _GEN_0 = mux(io_jump_flag_id, io_jump_address_id, _pc_T_1) @[src/main/scala/riscv/core/InstructionFetch.scala 31:31 32:16 34:16]
    node _GEN_1 = mux(io_instruction_valid, io_instruction_read_data, UInt<5>("h13")) @[src/main/scala/riscv/core/InstructionFetch.scala 24:32 25:24 39:24]
    node _GEN_2 = mux(io_instruction_valid, _GEN_0, pc) @[src/main/scala/riscv/core/InstructionFetch.scala 24:32 38:12]
    io_instruction_address <= pc @[src/main/scala/riscv/core/InstructionFetch.scala 41:28]
    io_instruction <= _GEN_1
    pc <= mux(reset, UInt<32>("h80000000"), _GEN_2) @[src/main/scala/riscv/core/InstructionFetch.scala 22:{21,21}]
