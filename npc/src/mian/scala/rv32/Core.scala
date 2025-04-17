package rv32

import chisel3._
import chisel3.util._
import Parameters._
import Parameters.Instructions._

class FetchStage{
    val pc = RegInit(START_ADDR)
    val inst = Wire(UInt(WORD_LEN.W))
    def connect(imem: ImemPortIo,exe: ExecuteStage) = {
        inst := imem.inst
        pc := MuxCase(pc + 4.U(WORD_LEN.W),Seq(
            exe.brFlag    -> exe.brTarget,
            exe.jmpFlag   -> exe.jmpTarget,
            (inst === ebreak) -> START_ADDR,
        ))
        imem.addr := pc
    }
}
class DecodeStage{
    def connect(fetch: FetchStage,exe: ExecuteStage,mem: Memory,gr: Mem[UInt]) = {
        val inst = fetch.inst
        val rs1Addr = inst(19,15)
        val rs2Addr = inst(24,20)
        val rdAddr = inst(11,7)

        val rs1Data = MuxCase(gr(rs1Addr),Seq(
            (rs1Addr === 0.U) -> 0.U(WORD_LEN.W)
        ))
        val rs2Data = MuxCase(gr(rs2Addr),Seq(
            (rs2Addr === 0.U) -> 0.U(WORD_LEN.W)
        ))
        
        val immI = inst(31,20)
        val immIsext = Cat(Fill(20,immI(11)),immI)
        val immS = Cat(inst(31,25),inst(11,7))
        val immSsext = Cat(Fill(20,immS(11)),immS)
        val immB = Cat(inst(31),inst(7),inst(30,25),inst(11,8))
        val immBsext = Cat(Fill(19,immB(11)),immB,0.U(1.W))
        val immJ = Cat(inst(31),inst(19,12),inst(20),inst(30,21))
        val immJsext = Cat(Fill(11,immJ(19)),immJ,0.U(1.W))
        val immU = Cat(inst(31,12))
        val immUsext = Cat(immU, 0.U(12.W))

        val List(aluOp,op1,op2,brType,memOp,regWrite,wbOp,immType) = ListLookup(
            inst,
            List(ALU_NONE,OP1_NONE,OP2_NONE,BR_NONE,MEM_NONE,WB_NONE,IMM_NONE)
            Array(
                auipc -> List(ALU_ADD,OP1_PC,OP2_IMM,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_U),
                lui   -> List(ALU_ADD,OP1_PC,OP2_IMM,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_U),
                
                lw    -> List(ALU_ADD,OP1_RS1,OP2_IMM,BR_NONE,MEM_LW,WB_EN,WB_MEM,IMM_I),
                lbu   -> List(ALU_ADD,OP1_RS1,OP2_IMM,BR_NONE,MEM_LBU,WB_EN,WB_MEM,IMM_I),
                lb    -> List(ALU_ADD,OP1_RS1,OP2_IMM,BR_NONE,MEM_LB,WB_EN,WB_MEM,IMM_I),
                lh    -> List(ALU_ADD,OP1_RS1,OP2_IMM,BR_NONE,MEM_LH,WB_EN,WB_MEM,IMM_I),
                lhu   -> List(ALU_ADD,OP1_RS1,OP2_IMM,BR_NONE,MEM_LHU,WB_EN,WB_MEM,IMM_I),
                andi  -> List(ALU_AND,OP1_RS1,OP2_IMM,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_I),
                addi  -> List(ALU_ADD,OP1_RS1,OP2_IMM,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_I),
                xori  -> List(ALU_XOR,OP1_RS1,OP2_IMM,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_I),
                ori   -> List(ALU_OR,OP1_RS1,OP2_IMM,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_I),
                srai  -> List(ALU_SRA,OP1_RS1,OP2_IMM,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_I),
                srli  -> List(ALU_SRL,OP1_RS1,OP2_IMM,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_I),
                slli  -> List(ALU_SLL,OP1_RS1,OP2_IMM,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_I),
                sltiu -> List(ALU_SLTU,OP1_RS1,OP2_IMM,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_I),
                slti  -> List(ALU_SLT,OP1_RS1,OP2_IMM,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_I),
                jalr  -> List(ALU_ADD,OP1_RS1,OP2_IMM,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_I),
                
                sb    -> List(ALU_ADD,OP1_RS1,OP2_IMM,BR_NONE,MEM_SB,WB_EN,WB_MEM,IMM_S),
                sw    -> List(ALU_ADD,OP1_RS1,OP2_IMM,BR_NONE,MEM_SW,WB_EN,WB_MEM,IMM_S),
                sh    -> List(ALU_ADD,OP1_RS1,OP2_IMM,BR_NONE,MEM_SH,WB_EN,WB_MEM,IMM_S),
                
                blt   -> List(ALU_SUB,OP1_RS1,OP2_RS2,BR_BLT,MEM_NONE,WB_NONE,IMM_B),
                bltu  -> List(ALU_SUB,OP1_RS1,OP2_RS2,BR_BLTU,MEM_NONE,WB_NONE,IMM_B),
                bge   -> List(ALU_SUB,OP1_RS1,OP2_RS2,BR_BGE,MEM_NONE,WB_NONE,IMM_B),
                bgeu  -> List(ALU_SUB,OP1_RS1,OP2_RS2,BR_BGEU,MEM_NONE,WB_NONE,IMM_B),
                beq   -> List(ALU_SUB,OP1_RS1,OP2_RS2,BR_BEQ,MEM_NONE,WB_NONE,IMM_B),
                bne   -> List(ALU_SUB,OP1_RS1,OP2_RS2,BR_BNE,MEM_NONE,WB_NONE,IMM_B),
                
                sra   -> List(ALU_SRA,OP1_RS1,OP2_RS2,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_NONE),
                srl   -> List(ALU_SRL,OP1_RS1,OP2_RS2,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_NONE),
                rem   -> List(ALU_REM,OP1_RS1,OP2_RS2,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_NONE),
                remu  -> List(ALU_REMU,OP1_RS1,OP2_RS2,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_NONE),
                divu  -> List(ALU_DIVU,OP1_RS1,OP2_RS2,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_NONE),
                div   -> List(ALU_DIV,OP1_RS1,OP2_RS2,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_NONE),
                mul   -> List(ALU_MUL,OP1_RS1,OP2_RS2,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_NONE),
                mulh  -> List(ALU_MULH,OP1_RS1,OP2_RS2,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_NONE),
                mulhu -> List(ALU_MULHU,OP1_RS1,OP2_RS2,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_NONE),
                and   -> List(ALU_AND,OP1_RS1,OP2_RS2,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_NONE),
                sll   -> List(ALU_SLL,OP1_RS1,OP2_RS2,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_NONE),
                add   -> List(ALU_ADD,OP1_RS1,OP2_RS2,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_NONE),
                sub   -> List(ALU_SUB,OP1_RS1,OP2_RS2,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_NONE),
                sltu  -> List(ALU_SLTU,OP1_RS1,OP2_RS2,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_NONE),
                slt   -> List(ALU_SLT,OP1_RS1,OP2_RS2,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_NONE),
                xor   -> List(ALU_XOR,OP1_RS1,OP2_RS2,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_NONE),
                or    -> List(ALU_OR,OP1_RS1,OP2_RS2,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_NONE), 

                jal   -> List(ALU_ADD,OP1_PC,OP2_IMM,BR_NONE,MEM_NONE,WB_EN,WB_ALU,IMM_J),

                ebreak -> List(ALU_NONE,OP1_NONE,OP2_NONE,BR_NONE,MEM_NONE,WB_NONE,IMM_NONE),
            )
        )
        val op1Data = MuxCase(0.U(WORD_LEN.W),Seq(
            (op1 === OP1_PC) -> pc,
            (op1 === OP1_RS1) -> rs1Data,
        ))
        val immData = MuxCase(0.U(WORD_LEN.W),Seq(
            (immType === IMM_I) -> immIsext,
            (immType === IMM_S) -> immSsext,
            (immType === IMM_B) -> immBsext,
            (immType === IMM_U) -> immUsext,
            (immType === IMM_J) -> immJsext,
        ))
        val op2Data = MuxCase(0.U(WORD_LEN.W),Seq(
            (op2 === OP2_RS2) -> rs2Data,
            (op2 === OP2_IMM) -> immData,
        ))
    }
}
class ExecuteStage{
    val brFlag = Wire(Bool())
    val brTarget = Wire(UInt(WORD_LEN.W))
    val jmpFlag = Wire(Bool())
    val aluOut = Wire(UInt(WORD_LEN.W))
    
    def connect(fetch: FetchStage,decode: DecodeStage) = {
        aluOut := MuxCase(0.U(WORD_LEN.W),Seq(
            (decode.aluOp === ALU_ADD) -> (decode.op1Data + decode.op2Data),
            (decode.aluOp === ALU_SUB) -> (decode.op1Data - decode.op2Data),
            (decode.aluOp === ALU_AND) -> (decode.op1Data & decode.op2Data),
            (decode.aluOp === ALU_OR) -> (decode.op1Data | decode.op2Data),
            (decode.aluOp === ALU_XOR) -> (decode.op1Data ^ decode.op2Data),
            (decode.aluOp === ALU_SLL) -> (decode.op1Data << decode.op2Data),
            (decode.aluOp === ALU_SRL) -> (decode.op1Data >> decode.op2Data),
            (decode.aluOp === ALU_SRA) -> (decode.op1Data.asSInt >> decode.op2Data),
            (decode.aluOp === ALU_SLT) -> (decode.op1Data.asSInt < decode.op2Data.asSInt),
            (decode.aluOp === ALU_SLTU) -> (decode.op1Data < decode.op2Data),
            (decode.aluOp === ALU_MUL) -> (decode.op1Data * decode.op2Data),
            (decode.aluOp === ALU_MULH) -> ((decode.op1Data * decode.op2Data) >> 16.U),
            (decode.aluOp === ALU_MULHU) -> ((decode.op1Data * decode.op2Data) >> 16.U),
            (decode.aluOp === ALU_MULHSU) -> ((decode.op1Data.asSInt * decode.op2Data.asSInt) >> 16.U),
            (decode.aluOp === ALU_DIV) -> (decode.op1Data / decode.op2Data),
            (decode.aluOp === ALU_DIVU) -> (decode.op1Data / decode.op2Data),
            (decode.aluOp === ALU_REM) -> (decode.op1Data % decode.op2Data),
            (decode.aluOp === ALU_REMU) -> (decode.op1Data % decode.op2Data),
            (decode.aluOp === ALU_NONE) -> 0.U(WORD_LEN.W),
        ))

        brFlag := MuxCase(false.B, Seq(
            (decode.brType === BR_BEQ) -> (decode.op1Data === decode.op2Data),
            (decode.brType === BR_BNE) -> (decode.op1Data =/= decode.op2Data),
            (decode.brType === BR_BLT) -> (decode.op1Data.asSInt < decode.op2Data.asSInt),
            (decode.brType === BR_BGE) -> (decode.op1Data.asSInt >= decode.op2Data.asSInt),
            (decode.brType === BR_BLTU) -> (decode.op1Data < decode.op2Data),
            (decode.brType === BR_BGEU) -> (decode.op1Data >= decode.op2Data),
        ))
        brTarget := fetch.pc + decode.immData
        jmpTarget := Mux(fetch.inst === jalr,(decode.op1Data + decode.immData) & ~1.U(WORD_LEN.W),decode.op2Data)
        jmpFlag := Mux((fetch.inst === jalr || fetch.inst === jal),true.B,false.B)
    }
    
}
class MemoryStage{
    
}
class WriteBackStage{
}