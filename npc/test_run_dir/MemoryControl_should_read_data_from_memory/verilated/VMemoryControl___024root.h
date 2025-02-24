// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See VMemoryControl.h for the primary calling header

#ifndef VERILATED_VMEMORYCONTROL___024ROOT_H_
#define VERILATED_VMEMORYCONTROL___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"

class VMemoryControl__Syms;

class VMemoryControl___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clock,0,0);
    VL_IN8(reset,0,0);
    VL_IN8(io_memory_read_enable,0,0);
    VL_IN8(io_memory_write_enable,0,0);
    VL_IN8(io_funct3,2,0);
    VL_OUT8(io_memory_bundle_write_enable,0,0);
    VL_OUT8(io_memory_bundle_write_strobe_0,0,0);
    VL_OUT8(io_memory_bundle_write_strobe_1,0,0);
    VL_OUT8(io_memory_bundle_write_strobe_2,0,0);
    VL_OUT8(io_memory_bundle_write_strobe_3,0,0);
    CData/*0:0*/ __VactContinue;
    VL_IN(io_alu_result,31,0);
    VL_IN(io_reg2_data,31,0);
    VL_OUT(io_wb_memory_read_data,31,0);
    VL_OUT(io_memory_bundle_address,31,0);
    VL_IN(io_memory_bundle_read_data,31,0);
    VL_OUT(io_memory_bundle_write_data,31,0);
    IData/*31:0*/ __VstlIterCount;
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<0> __VactTriggered;
    VlTriggerVec<0> __VnbaTriggered;

    // INTERNAL VARIABLES
    VMemoryControl__Syms* const vlSymsp;

    // CONSTRUCTORS
    VMemoryControl___024root(VMemoryControl__Syms* symsp, const char* v__name);
    ~VMemoryControl___024root();
    VL_UNCOPYABLE(VMemoryControl___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(std::atomic<uint32_t>* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
