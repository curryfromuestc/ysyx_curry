module ysyx_24120006_nextpc
#(
    parameter opcode_jal = 7'b1101111,
    parameter opcode_jalr = 7'b1100111,
    parameter opcode_branch = 7'b1100011,
    parameter func3_beq = 3'b000,
    parameter func3_bne = 3'b001,
    parameter func3_blt = 3'b100,
    parameter func3_bge = 3'b101,
    parameter func3_bltu = 3'b110,
    parameter func3_bgeu = 3'b111
)
(
    input wire [31:0] pc,
    input wire [31:0] instr,
    input wire [31:0] gpr_rs1,
    input wire [31:0] gpr_rs2,
    output wire [31:0] nextpc
);

wire is_jal , is_jalr , is_beq , is_bne , is_blt , is_bge , is_bltu , is_bgeu;
wire [31:0] immb,immj;
wire [31:0] adder;

assign is_jal = (instr[6:0] == opcode_jal);
assign is_jalr = (instr[6:0] == opcode_jalr);
assign is_beq = (instr[6:0] == opcode_branch) && (instr[14:12] == func3_beq);
assign is_bne = (instr[6:0] == opcode_branch) && (instr[14:12] == func3_bne);
assign is_blt = (instr[6:0] == opcode_branch) && (instr[14:12] == func3_blt);
assign is_bge = (instr[6:0] == opcode_branch) && (instr[14:12] == func3_bge);
assign is_bltu = (instr[6:0] == opcode_branch) && (instr[14:12] == func3_bltu);
assign is_bgeu = (instr[6:0] == opcode_branch) && (instr[14:12] == func3_bgeu);

assign immb = { {20{instr[31]}}, instr[7], instr[30:25], instr[11:8], 1'b0 };
assign immj = { {12{instr[31]}}, instr[19:12], instr[20], instr[30:21], 1'b0 };
/*adder是pc需要加上的这个值，不是最终的nextpc，
  //----------------------------------J---------------------------------------------
  INSTPAT("??????? ????? ????? ??? ????? 11011 11", jal    , J, R(rd) = s -> pc + 4; s -> dnpc += imm - 4;);
  INSTPAT("??????? ????? ????? ??? ????? 11001 11", jalr   , J, R(rd) = s -> pc + 4; s -> dnpc = (src1 + imm) & ~1);
  //----------------------------------B---------------------------------------------
  INSTPAT("??????? ????? ????? 000 ????? 11000 11", beq    , B, s -> dnpc += src1 == src2 ? imm - 4 : 0);
  INSTPAT("??????? ????? ????? 001 ????? 11000 11", bne    , B, s -> dnpc += src1 != src2 ? imm - 4 : 0);
  INSTPAT("??????? ????? ????? 100 ????? 11000 11", blt    , B, s -> dnpc += (sword_t)src1 < (sword_t)src2 ? imm - 4 : 0);
  INSTPAT("??????? ????? ????? 101 ????? 11000 11", bge    , B, s -> dnpc += src1 >= src2 ? imm - 4 : 0);
  INSTPAT("??????? ????? ????? 110 ????? 11000 11", bltu   , B, s -> dnpc += (word_t)src1 < (word_t)src2 ? imm - 4 : 0);
  INSTPAT("??????? ????? ????? 111 ????? 11000 11", bgeu   , B, s -> dnpc += src1 >= src2 ? imm - 4 : 0);
*/
assign adder = is_jal ? immj : 
              is_jalr ? (gpr_rs1 + immb) & ~1 :
              is_beq ? (gpr_rs1 == gpr_rs2 ? immb : 0) :
              is_bne ? (gpr_rs1 != gpr_rs2 ? immb : 0) :
              is_blt ? ((signed'(gpr_rs1) < signed'(gpr_rs2)) ? immb : 0) :
              is_bge ? (gpr_rs1 >= gpr_rs2 ? immb : 0) :
              is_bltu ? ((gpr_rs1 < gpr_rs2) ? immb : 0) :
              is_bgeu ? (gpr_rs1 >= gpr_rs2 ? immb : 0) :
              4;

assign nextpc = adder+pc;

endmodule