// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See VInstructionFetch.h for the primary calling header

#ifndef VERILATED_VINSTRUCTIONFETCH___024ROOT_H_
#define VERILATED_VINSTRUCTIONFETCH___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"

class VInstructionFetch__Syms;

class VInstructionFetch___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clock,0,0);
    VL_IN8(reset,0,0);
    VL_IN8(io_jump_flag_id,0,0);
    VL_IN8(io_instruction_valid,0,0);
    CData/*0:0*/ __Vtrigrprev__TOP__clock;
    CData/*0:0*/ __VactContinue;
    VL_IN(io_jump_address_id,31,0);
    VL_IN(io_instruction_read_data,31,0);
    VL_OUT(io_instruction_address,31,0);
    VL_OUT(io_instruction,31,0);
    IData/*31:0*/ InstructionFetch__DOT__pc;
    IData/*31:0*/ InstructionFetch__DOT___pc_T_1;
    IData/*31:0*/ __VstlIterCount;
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    VInstructionFetch__Syms* const vlSymsp;

    // CONSTRUCTORS
    VInstructionFetch___024root(VInstructionFetch__Syms* symsp, const char* v__name);
    ~VInstructionFetch___024root();
    VL_UNCOPYABLE(VInstructionFetch___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(std::atomic<uint32_t>* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
