// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See VInstructionDecode.h for the primary calling header

#ifndef VERILATED_VINSTRUCTIONDECODE___024ROOT_H_
#define VERILATED_VINSTRUCTIONDECODE___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"

class VInstructionDecode__Syms;

class VInstructionDecode___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clock,0,0);
    VL_IN8(reset,0,0);
    VL_OUT8(io_regs_reg1_read_address,4,0);
    VL_OUT8(io_regs_reg2_read_address,4,0);
    VL_OUT8(io_ex_aluop1_source,0,0);
    VL_OUT8(io_ex_aluop2_source,0,0);
    VL_OUT8(io_memory_read_enable,0,0);
    VL_OUT8(io_memory_write_enable,0,0);
    VL_OUT8(io_wb_reg_write_source,1,0);
    VL_OUT8(io_reg_write_enable,0,0);
    VL_OUT8(io_reg_write_address,4,0);
    CData/*0:0*/ __VactContinue;
    VL_IN(io_instruction,31,0);
    VL_OUT(io_ex_immediate,31,0);
    IData/*31:0*/ __VstlIterCount;
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<0> __VactTriggered;
    VlTriggerVec<0> __VnbaTriggered;

    // INTERNAL VARIABLES
    VInstructionDecode__Syms* const vlSymsp;

    // CONSTRUCTORS
    VInstructionDecode___024root(VInstructionDecode__Syms* symsp, const char* v__name);
    ~VInstructionDecode___024root();
    VL_UNCOPYABLE(VInstructionDecode___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(std::atomic<uint32_t>* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
