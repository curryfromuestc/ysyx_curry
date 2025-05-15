package rv32

import chisel3._
import chisel3.util._
import Parameters._
import Instructions._

//         ┌─┐          ┌─┐          ┌─┐           ┌─┐
// ┌────┐  │/│  ┌────┐  │/│  ┌────┐  │/│  ┌─────┐  │/│  ┌────┐
// │    │  │/│  │    │  │/│  │    │  │/│  │     │  │/│  │    │
// │ IF ├─►│/├─►│ ID ├─►│/├─►│ EX ├─►│/├─►│ MEM ├─►│/├─►│ WB │
// │    │  │/│  │    │  │/│  │    │  │/│  │     │  │/│  │    │
// └────┘  │/│  └────┘  │/│  └────┘  │/│  └─────┘  │/│  └────┘
//         └─┘          └─┘          └─┘           └─┘
//        IF/ID        IF/ID        IF/MEM       MEM/ID
//      registers    registers    registers     registers
class FetchStage{
    val stallFlag = Wire(Bool())
    val pcReg = RegInit(0.U(WORD_LEN.W))
    val instReg = RegInit(0.U(WORD_LEN.W))
    def connect(imem: ImemPortIo,exe: ExecuteStage, csr: Mem[UInt]) = {
        val inst = imem.inst
        val pc = RegInit(START_PC)
        pcReg := MuxCase(pcReg + 4.U(WORD_LEN.W),Seq(
            exe.brFlag    -> exe.brTarget,
            exe.jmpFlag   -> exe.aluOut,
            (inst === ECALL) -> csr(0x305),
            stallFlag     -> pc,
        ))
        imem.addr := pc
        pcReg := Mux(stallFlag,pcReg,pc)

        instReg := MuxCase(inst,Seq(
            (exe.brFlag || exe.jmpFlag) -> BUBBLE,
            stallFlag     -> instReg,
        ))
    }
}
class DecodeStage{
    //ID/EX流水线寄存器
    val inst = Wire(UInt(WORD_LEN.W))
    val pcReg = RegInit(0.U(WORD_LEN.W))
    val wbAddrReg = RegInit(0.U(WORD_LEN.W))
    val op1DataReg = RegInit(0.U(WORD_LEN.W))
    val op2DataReg = RegInit(0.U(WORD_LEN.W))
    val rs1DataReg = RegInit(0.U(WORD_LEN.W))
    val rs2DataReg = RegInit(0.U(WORD_LEN.W))
    val exeFunReg = RegInit(0.U(EXE_FUN_LEN.W))
    val memWenReg = RegInit(0.U(MEN_LEN.W))
    val rfWenReg = RegInit(0.U(REN_LEN.W))
    val wbSelReg = RegInit(0.U(WB_SEL_LEN.W))
    val csrAddrReg = RegInit(0.U(CSR_ADDR_LEN.W))
    val csrCmdReg = RegInit(0.U(CSR_LEN.W))
    val immIsextReg = RegInit(0.U(WORD_LEN.W))
    val immSsextReg = RegInit(0.U(WORD_LEN.W))
    val immBsextReg = RegInit(0.U(WORD_LEN.W))
    val immUshiftedReg = RegInit(0.U(WORD_LEN.W))
    val immZuextReg = RegInit(0.U(WORD_LEN.W))

    def connectStallFlag(fetch: FetchStage) = {
        val rs1Addr = fetch.instReg(19,15)
        val rs2Addr = fetch.instReg(24,20)

        fetch.stallFlag := (
            rfWenReg === REN_SCALAR && rs1Addr =/= 0.U && rs1Addr === wbAddrReg
        )||(
            rfWenReg === REN_SCALAR && rs2Addr =/= 0.U && rs2Addr === wbAddrReg
        )
    }

    def connect(fetch: FetchStage,exe: ExecuteStage,mem: MemoryStage,gr: Mem[UInt]) = {
        connectStallFlag(fetch)

        inst := Mux(exe.brFlag || exe.jmpFlag || fetch.stallFlag,BUBBLE,fetch.instReg)
        val rs1Addr = inst(19,15)
        val rs2Addr = inst(24,20)
        val wbAddr = inst(11,7)

        val rs1Data = MuxCase(gr(rs1Addr),Seq(
            (rs1Addr === 0.U) -> 0.U(WORD_LEN.W),
            (rs1Addr === exe.wbAddrReg && exe.rfWenReg === REN_SCALAR) -> mem.wbData,
            (rs1Addr === exe.wbAddrReg && exe.rfWenReg === REN_SCALAR) -> mem.wbDataReg,
        ))
        val rs2Data = MuxCase(gr(rs2Addr),Seq(
            (rs2Addr === 0.U) -> 0.U(WORD_LEN.W),
            (rs2Addr === exe.wbAddrReg && exe.rfWenReg === REN_SCALAR) -> mem.wbData,
            (rs2Addr === exe.wbAddrReg && exe.rfWenReg === REN_SCALAR) -> mem.wbDataReg,
        ))
        
        val immI = inst(31,20)
        val immIsext = Cat(Fill(20,immI(11)),immI)
        val immS = Cat(inst(31,25),inst(11,7))
        val immSsext = Cat(Fill(20,immS(11)),immS)
        val immB = Cat(inst(31),inst(7),inst(30,25),inst(11,8))
        val immBsext = Cat(Fill(19,immB(11)),immB,0.U(1.W))
        val immJ = Cat(inst(31),inst(19,12),inst(20),inst(30,21))
        val immJsext = Cat(Fill(11,immJ(19)),immJ,0.U(1.W))

        val immU = inst(31,12)
        val immUshifted = Cat(immU,Fill(12,0.U))

        val immZ = inst(19,15)
        val immZuext = Cat(Fill(27,0.U),immZ)

        val decoded = ListLookup(
            inst,
            List(ALU_NONE, OP1_RS1, OP2_RS2, MEN_NONE, REN_NONE, WB_NONE,CSR_NONE),
            Array(
                // 2.6 Load and Store Instructions
                LW      -> List(ALU_ADD,  OP1_RS1,  OP2_IMI,  MEN_NONE,   REN_SCALAR, WB_MEM, CSR_NONE), // x[rs1] + sext(imm_i)
                SW      -> List(ALU_ADD,  OP1_RS1,  OP2_IMS,  MEN_SCALAR, REN_NONE,   WB_NONE, CSR_NONE), // x[rs1] + sext(imm_s)
                // 2.4 Integer Computational Instructions
                ADD     -> List(ALU_ADD,  OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_SCALAR, WB_ALU, CSR_NONE), // x[rs1] + x[rs2]
                ADDI    -> List(ALU_ADD,  OP1_RS1,  OP2_IMI,  MEN_NONE,   REN_SCALAR, WB_ALU, CSR_NONE), // x[rs1] + sext(imm_i)
                SUB     -> List(ALU_SUB,  OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_SCALAR, WB_ALU, CSR_NONE), // x[rs1] - x[rs2]
                AND     -> List(ALU_AND,  OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_SCALAR, WB_ALU, CSR_NONE), // x[rs1] & x[rs2]
                OR      -> List(ALU_OR,   OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_SCALAR, WB_ALU, CSR_NONE), // x[rs1] | x[rs2]
                XOR     -> List(ALU_XOR,  OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_SCALAR, WB_ALU, CSR_NONE), // x[rs1] ^ x[rs2]
                ANDI    -> List(ALU_AND,  OP1_RS1,  OP2_IMI,  MEN_NONE,   REN_SCALAR, WB_ALU, CSR_NONE), // x[rs1] & sext(imm_i)
                ORI     -> List(ALU_OR ,  OP1_RS1,  OP2_IMI,  MEN_NONE,   REN_SCALAR, WB_ALU, CSR_NONE), // x[rs1] | sext(imm_i)
                XORI    -> List(ALU_XOR,  OP1_RS1,  OP2_IMI,  MEN_NONE,   REN_SCALAR, WB_ALU, CSR_NONE), // x[rs1] ^ sext(imm_i)
                SLL     -> List(ALU_SLL,  OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_SCALAR, WB_ALU, CSR_NONE), // x[rs1] << x[rs2](4,0)
                SRL     -> List(ALU_SRL,  OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_SCALAR, WB_ALU, CSR_NONE), // x[rs1] >>u x[rs2](4,0)
                SRA     -> List(ALU_SRA,  OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_SCALAR, WB_ALU, CSR_NONE), // x[rs1] >>s x[rs2](4,0)
                SLLI    -> List(ALU_SLL,  OP1_RS1,  OP2_IMI,  MEN_NONE,   REN_SCALAR, WB_ALU, CSR_NONE), // x[rs1] << imm_i_sext(4,0)
                SRLI    -> List(ALU_SRL,  OP1_RS1,  OP2_IMI,  MEN_NONE,   REN_SCALAR, WB_ALU, CSR_NONE), // x[rs1] >>u imm_i_sext(4,0)
                SRAI    -> List(ALU_SRA,  OP1_RS1,  OP2_IMI,  MEN_NONE,   REN_SCALAR, WB_ALU, CSR_NONE), // x[rs1] >>s imm_i_sext(4,0)
                SLT     -> List(ALU_SLT,  OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_SCALAR, WB_ALU, CSR_NONE), // x[rs1] <s x[rs2]
                SLTU    -> List(ALU_SLTU, OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_SCALAR, WB_ALU, CSR_NONE), // x[rs1] <u x[rs2]
                SLTI    -> List(ALU_SLT,  OP1_RS1,  OP2_IMI,  MEN_NONE,   REN_SCALAR, WB_ALU, CSR_NONE), // x[rs1] <s imm_i_sext
                SLTIU   -> List(ALU_SLTU, OP1_RS1,  OP2_IMI,  MEN_NONE,   REN_SCALAR, WB_ALU, CSR_NONE), // x[rs1] <u imm_i_sext
                LUI     -> List(ALU_ADD,  OP1_NONE, OP2_IMU,  MEN_NONE,   REN_SCALAR, WB_ALU, CSR_NONE), // sext(imm_u[31:12] << 12)
                AUIPC   -> List(ALU_ADD,  OP1_PC,   OP2_IMU,  MEN_NONE,   REN_SCALAR, WB_ALU, CSR_NONE), // PC + sext(imm_u[31:12] << 12)
                // 2.5 Control Transfer Instructions
                BEQ     -> List(BR_BEQ,   OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_NONE,   WB_NONE, CSR_NONE), // x[rs1] === x[rs2] then PC+sext(imm_b)
                BNE     -> List(BR_BNE,   OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_NONE,   WB_NONE, CSR_NONE), // x[rs1] =/= x[rs2] then PC+sext(imm_b)
                BGE     -> List(BR_BGE,   OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_NONE,   WB_NONE, CSR_NONE), // x[rs1] >=s x[rs2] then PC+sext(imm_b)
                BGEU    -> List(BR_BGEU,  OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_NONE,   WB_NONE, CSR_NONE), // x[rs1] >=u x[rs2] then PC+sext(imm_b)
                BLT     -> List(BR_BLT,   OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_NONE,   WB_NONE, CSR_NONE), // x[rs1] <s x[rs2]  then PC+sext(imm_b)
                BLTU    -> List(BR_BLTU,  OP1_RS1,  OP2_RS2,  MEN_NONE,   REN_NONE,   WB_NONE, CSR_NONE), // x[rs1] <u x[rs2]  then PC+sext(imm_b)
                JAL     -> List(ALU_ADD,  OP1_PC,   OP2_IMJ,  MEN_NONE,   REN_SCALAR, WB_PC, CSR_NONE), // x[rd] <- PC+4 and PC+sext(imm_j)
                JALR    -> List(ALU_JALR, OP1_RS1,  OP2_IMI,  MEN_NONE,   REN_SCALAR, WB_PC, CSR_NONE), // x[rd] <- PC+4 and (x[rs1]+sext(imm_i))&~1
                
                CSRRWI  -> List(ALU_RS1,  OP1_IMZ,  OP2_NONE, MEN_NONE,   REN_SCALAR, WB_CSR,   CSR_W), 
                CSRRS   -> List(ALU_RS1,  OP1_RS1,  OP2_NONE, MEN_NONE,   REN_SCALAR, WB_CSR,   CSR_S), 
                CSRRSI  -> List(ALU_RS1,  OP1_IMZ,  OP2_NONE, MEN_NONE,   REN_SCALAR, WB_CSR,   CSR_S), 
                CSRRC   -> List(ALU_RS1,  OP1_RS1,  OP2_NONE, MEN_NONE,   REN_SCALAR, WB_CSR,   CSR_C), 
                CSRRCI  -> List(ALU_RS1,  OP1_IMZ,  OP2_NONE, MEN_NONE,   REN_SCALAR, WB_CSR,   CSR_C), 
                
                // 2.8 Environment Call and Breakpoints
                ECALL  -> List(ALU_NONE, OP1_NONE, OP2_NONE, MEN_NONE,   REN_NONE,   WB_NONE, CSR_E),

                VSETVLI -> List(ALU_NONE, OP1_NONE, OP2_NONE, MEN_NONE,   REN_SCALAR, WB_VL,    CSR_V),
                VLE     -> List(ALU_RS1,  OP1_RS1,  OP2_NONE, MEN_NONE,   REN_VECTOR, WB_MEM_V, CSR_NONE),
            ),
        )

        val exeFun = decoded(0)
        val op1Sel = decoded(1)
        val op2Sel = decoded(2)
        val memWen = decoded(3)
        val rfWen = decoded(4)
        val wbSel = decoded(5)
        val csrCmd = decoded(6)

        val op1Data = MuxCase(0.U(WORD_LEN.W),Seq(
            (op1Sel === OP1_PC) -> fetch.pcReg,
            (op1Sel === OP1_RS1) -> rs1Data,
            (op1Sel === OP1_IMZ) -> immZuext,
        ))
        val op2Data = MuxCase(0.U(WORD_LEN.W),Seq(
            (op2Sel === OP2_RS2) -> rs2Data,
            (op2Sel === OP2_IMI) -> immIsext,
            (op2Sel === OP2_IMS) -> immSsext,
            (op2Sel === OP2_IMJ) -> immJsext,
            (op2Sel === OP2_IMU) -> immUshifted,
        ))
        val csrAddr = Mux(
            csrCmd === CSR_E,
            0x342.U(CSR_ADDR_LEN.W),
            inst(31,20),
        )

        //记录ID
        pcReg := fetch.pcReg
        op1DataReg := op1Data
        op2DataReg := op2Data
        rs1DataReg := rs1Data
        rs2DataReg := rs2Data
        wbAddrReg := wbAddr
        rfWenReg := rfWen
        exeFunReg := exeFun
        wbSelReg := wbSel
        immIsextReg := immIsext
        immSsextReg := immSsext
        immBsextReg := immBsext
        immUshiftedReg := immUshifted
        immZuextReg := immZuext
        csrAddrReg := csrAddr
        csrCmdReg := csrCmd
        memWenReg := memWen
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
            (decode.exeFun === ALU_SLL) -> (decode.op1Data << decode.op2Data(4,0)),
            (decode.exeFun === ALU_SRL) -> (decode.op1Data >> decode.op2Data(4,0)),
            (decode.exeFun === ALU_SRA) -> (decode.op1Data.asSInt >> decode.op2Data(4,0)).asUInt,
            (decode.exeFun === ALU_SLT) -> Mux(decode.op1Data.asSInt < decode.op2Data.asSInt, 1.U, 0.U),
            (decode.exeFun === ALU_SLTU) -> Mux(decode.op1Data < decode.op2Data, 1.U, 0.U),
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
        val imem = Flipped(new ImemPortIo)
        val dmem = Flipped(new DmemPortIo)
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

    val ebreak = Module(new Ebreak())
    ebreak.io.instruction := fetch.inst
}