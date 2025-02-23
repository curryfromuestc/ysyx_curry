// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VInstructionFetch.h for the primary calling header

#include "verilated.h"

#include "VInstructionFetch__Syms.h"
#include "VInstructionFetch___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void VInstructionFetch___024root___dump_triggers__stl(VInstructionFetch___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void VInstructionFetch___024root___eval_triggers__stl(VInstructionFetch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionFetch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionFetch___024root___eval_triggers__stl\n"); );
    // Body
    vlSelf->__VstlTriggered.at(0U) = (0U == vlSelf->__VstlIterCount);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VInstructionFetch___024root___dump_triggers__stl(vlSelf);
    }
#endif
}
