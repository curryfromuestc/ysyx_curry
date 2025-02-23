// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See VExecute.h for the primary calling header

#ifndef VERILATED_VEXECUTE___024ROOT_H_
#define VERILATED_VEXECUTE___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"

class VExecute__Syms;

class VExecute___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clock,0,0);
    VL_IN8(reset,0,0);
    VL_IN8(io_aluop1_source,0,0);
    VL_IN8(io_aluop2_source,0,0);
    VL_OUT8(io_if_jump_flag,0,0);
    CData/*0:0*/ __VactContinue;
    VL_IN(io_instruction,31,0);
    VL_IN(io_instruction_address,31,0);
    VL_IN(io_reg1_data,31,0);
    VL_IN(io_reg2_data,31,0);
    VL_IN(io_immediate,31,0);
    VL_OUT(io_mem_alu_result,31,0);
    VL_OUT(io_if_jump_address,31,0);
    IData/*31:0*/ __VstlIterCount;
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<0> __VactTriggered;
    VlTriggerVec<0> __VnbaTriggered;

    // INTERNAL VARIABLES
    VExecute__Syms* const vlSymsp;

    // CONSTRUCTORS
    VExecute___024root(VExecute__Syms* symsp, const char* v__name);
    ~VExecute___024root();
    VL_UNCOPYABLE(VExecute___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(std::atomic<uint32_t>* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
