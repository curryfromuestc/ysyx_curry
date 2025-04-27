package rv32

import chisel3._
import chisel3.util._
import Parameters._
import Instructions._

//                             
// +----+    +----+    +----+    +----+    +----+
// |    |    |    |    |    |    |    |    |    |
// | IF |->  | ID |->  | EX |->  | MEM|->  | WB |
// |    |    |    |    |    |    |    |    |    |
// +----+    +----+    +----+    +----+    +----+
//         
//        
class FetchStage{
    val pc = RegInit(START_PC)
    val inst = Wire(UInt(WORD_LEN.W))
    def connect(imem: ImemPortIo,exe: ExecuteStage) = {
        inst := imem.inst
        pc := MuxCase(pc + 4.U(WORD_LEN.W),Seq(
            exe.brFlag    -> exe.brTarget,
            exe.jmpFlag   -> exe.aluOut,
            (inst === EBREAK) -> START_PC,
        ))
        imem.addr := pc
    }
}
class DecodeStage{
    val exeFun = Wire(UInt(EXE_FUN_LEN.W))
    val op1Sel = Wire(UInt(OP1_LEN.W))
    val op2Sel = Wire(UInt(OP2_LEN.W))
    val memWen = Wire(UInt(MEN_LEN.W))
    val rfWen = Wire(UInt(REN_LEN.W))
    val wbSel = Wire(UInt(WB_SEL_LEN.W))
    val op1Data = Wire(UInt(WORD_LEN.W))
    val op2Data = Wire(UInt(WORD_LEN.W))
    val immIsext = Wire(UInt(WORD_LEN.W))
    val immSsext = Wire(UInt(WORD_LEN.W))
    val immBsext = Wire(UInt(WORD_LEN.W))
    val immJsext = Wire(UInt(WORD_LEN.W))
    val immUsext = Wire(UInt(WORD_LEN.W))
    val rdAddr = Wire(UInt(5.W))
    def connect(fetch: FetchStage,exe: ExecuteStage,mem: MemoryStage,gr: Mem[UInt]) = {
        val inst = fetch.inst
        val rs1Addr = inst(19,15)
        val rs2Addr = inst(24,20)
        rdAddr := inst(11,7)

        val rs1Data = MuxCase(gr(rs1Addr),Seq(
            (rs1Addr === 0.U) -> 0.U(WORD_LEN.W)
        ))
        val rs2Data = MuxCase(gr(rs2Addr),Seq(
            (rs2Addr === 0.U) -> 0.U(WORD_LEN.W)
        ))
        
        val immI = inst(31,20)
        immIsext := Cat(Fill(20,immI(11)),immI)
        val immS = Cat(inst(31,25),inst(11,7))
        immSsext := Cat(Fill(20,immS(11)),immS)
        val immB = Cat(inst(31),inst(7),inst(30,25),inst(11,8))
        immBsext := Cat(Fill(19,immB(11)),immB,0.U(1.W))
        val immJ = Cat(inst(31),inst(19,12),inst(20),inst(30,21))
        immJsext := Cat(Fill(11,immJ(19)),immJ,0.U(1.W))
        val immU = Cat(inst(31,12))
        immUsext := Cat(immU, 0.U(12.W))

        val List(exeFun, op1Sel, op2Sel, memWen, rfWen, wbSel) = ListLookup(
        inst,
        List(ALU_NONE, OP1_RS1, OP2_RS2, MEN_NONE, REN_NONE, WB_NONE),
        Array(
            // 2.6 Load and Store Instructions
            LW      -> List(ALU_ADD,  OP1_RS1,  OP2_IMI,  MEN_NONE,   REN_SCALAR, WB_MEM), // x[rs1] + sext(imm_i)
            SW      -> List(ALU_ADD,  OP1_RS1,  OP2_IMS,  MEN_SCALAR, REN_NONE,   WB_NONE), // x[rs1] + sext(imm_s)
            // 2.4 Integer Computational Instructions
            ADD     -> List(ALU_ADD,  OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_SCALAR, WB_ALU), // x[rs1] + x[rs2]
            ADDI    -> List(ALU_ADD,  OP1_RS1,  OP2_IMI,  MEN_NONE,   REN_SCALAR, WB_ALU), // x[rs1] + sext(imm_i)
            SUB     -> List(ALU_SUB,  OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_SCALAR, WB_ALU), // x[rs1] - x[rs2]
            AND     -> List(ALU_AND,  OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_SCALAR, WB_ALU), // x[rs1] & x[rs2]
            OR      -> List(ALU_OR,   OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_SCALAR, WB_ALU), // x[rs1] | x[rs2]
            XOR     -> List(ALU_XOR,  OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_SCALAR, WB_ALU), // x[rs1] ^ x[rs2]
            ANDI    -> List(ALU_AND,  OP1_RS1,  OP2_IMI,  MEN_NONE,   REN_SCALAR, WB_ALU), // x[rs1] & sext(imm_i)
            ORI     -> List(ALU_OR ,  OP1_RS1,  OP2_IMI,  MEN_NONE,   REN_SCALAR, WB_ALU), // x[rs1] | sext(imm_i)
            XORI    -> List(ALU_XOR,  OP1_RS1,  OP2_IMI,  MEN_NONE,   REN_SCALAR, WB_ALU), // x[rs1] ^ sext(imm_i)
            SLL     -> List(ALU_SLL,  OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_SCALAR, WB_ALU), // x[rs1] << x[rs2](4,0)
            SRL     -> List(ALU_SRL,  OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_SCALAR, WB_ALU), // x[rs1] >>u x[rs2](4,0)
            SRA     -> List(ALU_SRA,  OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_SCALAR, WB_ALU), // x[rs1] >>s x[rs2](4,0)
            SLLI    -> List(ALU_SLL,  OP1_RS1,  OP2_IMI,  MEN_NONE,   REN_SCALAR, WB_ALU), // x[rs1] << imm_i_sext(4,0)
            SRLI    -> List(ALU_SRL,  OP1_RS1,  OP2_IMI,  MEN_NONE,   REN_SCALAR, WB_ALU), // x[rs1] >>u imm_i_sext(4,0)
            SRAI    -> List(ALU_SRA,  OP1_RS1,  OP2_IMI,  MEN_NONE,   REN_SCALAR, WB_ALU), // x[rs1] >>s imm_i_sext(4,0)
            SLT     -> List(ALU_SLT,  OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_SCALAR, WB_ALU), // x[rs1] <s x[rs2]
            SLTU    -> List(ALU_SLTU, OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_SCALAR, WB_ALU), // x[rs1] <u x[rs2]
            SLTI    -> List(ALU_SLT,  OP1_RS1,  OP2_IMI,  MEN_NONE,   REN_SCALAR, WB_ALU), // x[rs1] <s imm_i_sext
            SLTIU   -> List(ALU_SLTU, OP1_RS1,  OP2_IMI,  MEN_NONE,   REN_SCALAR, WB_ALU), // x[rs1] <u imm_i_sext
            LUI     -> List(ALU_ADD,  OP1_NONE, OP2_IMU,  MEN_NONE,   REN_SCALAR, WB_ALU), // sext(imm_u[31:12] << 12)
            AUIPC   -> List(ALU_ADD,  OP1_PC,   OP2_IMU,  MEN_NONE,   REN_SCALAR, WB_ALU), // PC + sext(imm_u[31:12] << 12)
            // 2.5 Control Transfer Instructions
            BEQ     -> List(BR_BEQ,   OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_NONE,   WB_NONE), // x[rs1] === x[rs2] then PC+sext(imm_b)
            BNE     -> List(BR_BNE,   OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_NONE,   WB_NONE), // x[rs1] =/= x[rs2] then PC+sext(imm_b)
            BGE     -> List(BR_BGE,   OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_NONE,   WB_NONE), // x[rs1] >=s x[rs2] then PC+sext(imm_b)
            BGEU    -> List(BR_BGEU,  OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_NONE,   WB_NONE), // x[rs1] >=u x[rs2] then PC+sext(imm_b)
            BLT     -> List(BR_BLT,   OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_NONE,   WB_NONE), // x[rs1] <s x[rs2]  then PC+sext(imm_b)
            BLTU    -> List(BR_BLTU,  OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_NONE,   WB_NONE), // x[rs1] <u x[rs2]  then PC+sext(imm_b)
            JAL     -> List(ALU_ADD,  OP1_PC,   OP2_IMJ,  MEN_NONE,   REN_SCALAR, WB_PC), // x[rd] <- PC+4 and PC+sext(imm_j)
            JALR    -> List(ALU_JALR, OP1_RS1,  OP2_IMI,  MEN_NONE,   REN_SCALAR, WB_PC), // x[rd] <- PC+4 and (x[rs1]+sext(imm_i))&~1
            // 2.8 Environment Call and Breakpoints
            EBREAK  -> List(ALU_NONE, OP1_NONE, OP2_NONE, MEN_NONE,   REN_NONE,   WB_NONE),
        ),
        )
        op1Data := MuxCase(0.U(WORD_LEN.W),Seq(
            (op1Sel === OP1_PC) -> fetch.pc,
            (op1Sel === OP1_RS1) -> rs1Data,
        ))
        op2Data := MuxCase(0.U(WORD_LEN.W),Seq(
            (op2Sel === OP2_RS2) -> rs2Data,
            (op2Sel === OP2_IMI) -> immIsext,
            (op2Sel === OP2_IMS) -> immSsext,
            (op2Sel === OP2_IMJ) -> immJsext,
            (op2Sel === OP2_IMU) -> immUsext,
        ))  

        exeFun := exeFun
        op1Sel := op1Sel
        op2Sel := op2Sel
        memWen := memWen
        rfWen := rfWen
        wbSel := wbSel
    }
}
class ExecuteStage{
    val brFlag = Wire(Bool())
    val brTarget = Wire(UInt(WORD_LEN.W))
    val jmpFlag = Wire(Bool())
    val aluOut = Wire(UInt(WORD_LEN.W))
    
    def connect(fetch: FetchStage,decode: DecodeStage) = {
        aluOut := MuxCase(0.U(WORD_LEN.W),Seq(
            (decode.exeFun === ALU_ADD) -> (decode.op1Data + decode.op2Data),
            (decode.exeFun === ALU_SUB) -> (decode.op1Data - decode.op2Data),
            (decode.exeFun === ALU_AND) -> (decode.op1Data & decode.op2Data),
            (decode.exeFun === ALU_OR) -> (decode.op1Data | decode.op2Data),
            (decode.exeFun === ALU_XOR) -> (decode.op1Data ^ decode.op2Data),
            (decode.exeFun === ALU_SLL) -> (decode.op1Data << decode.op2Data),
            (decode.exeFun === ALU_SRL) -> (decode.op1Data >> decode.op2Data),
            (decode.exeFun === ALU_SRA) -> (decode.op1Data.asSInt >> decode.op2Data),
            (decode.exeFun === ALU_SLT) -> (decode.op1Data.asSInt < decode.op2Data.asSInt),
            (decode.exeFun === ALU_SLTU) -> (decode.op1Data < decode.op2Data),
            (decode.exeFun === ALU_JALR) -> ((decode.op1Data + decode.op2Data) & ~1.U(WORD_LEN.W)),
            (decode.exeFun === ALU_RS1) -> decode.op1Data,
        ))

        brFlag := MuxCase(false.B, Seq(
            (decode.exeFun === BR_BEQ) -> (decode.op1Data === decode.op2Data),
            (decode.exeFun === BR_BNE) -> (decode.op1Data =/= decode.op2Data),
            (decode.exeFun === BR_BLT) -> (decode.op1Data.asSInt < decode.op2Data.asSInt),
            (decode.exeFun === BR_BGE) -> (decode.op1Data.asSInt >= decode.op2Data.asSInt),
            (decode.exeFun === BR_BLTU) -> (decode.op1Data < decode.op2Data),
            (decode.exeFun === BR_BGEU) -> (decode.op1Data >= decode.op2Data),
        ))
        brTarget := fetch.pc + decode.immBsext
        jmpFlag := decode.wbSel === WB_PC
    }
    
}
class MemoryStage{
    val wbData = Wire(UInt(WORD_LEN.W))
    def connect(fetch: FetchStage,dmem: DmemPortIo,decode: DecodeStage,exe: ExecuteStage) = {
        dmem.addr := exe.aluOut
        dmem.data := decode.op2Data
        dmem.wen := decode.memWen === MEN_SCALAR
        wbData := MuxCase(exe.aluOut,Seq(
            (decode.wbSel === WB_MEM) -> dmem.rdata,
            (decode.wbSel === WB_PC) -> (fetch.pc + 4.U(WORD_LEN.W)),
            (decode.wbSel === WB_NONE) -> 0.U(WORD_LEN.W),
        ))
    }
}
class WriteBackStage{
    def connect(mem: MemoryStage,decode: DecodeStage,exe: ExecuteStage,gr: Mem[UInt]) = {
        gr(decode.rdAddr) := mem.wbData
    }
}

class Core extends Module{
    val io = IO(new Bundle{
        val imem = new ImemPortIo()
        val dmem = new DmemPortIo()
    })
    val fetch = new FetchStage()
    val decode = new DecodeStage()
    val execute = new ExecuteStage()
    val memory = new MemoryStage()
    val writeback = new WriteBackStage()

    val gr = Mem(16,UInt(WORD_LEN.W))

    fetch.connect(io.imem,execute)
    decode.connect(fetch,execute,memory,gr)
    execute.connect(fetch,decode)
    memory.connect(fetch,io.dmem,decode,execute)
    writeback.connect(memory,decode,execute,gr)
}