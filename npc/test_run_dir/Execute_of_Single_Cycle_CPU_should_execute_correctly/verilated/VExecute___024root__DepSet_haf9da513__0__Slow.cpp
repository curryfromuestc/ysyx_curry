// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VExecute.h for the primary calling header

#include "verilated.h"

#include "VExecute___024root.h"

VL_ATTR_COLD void VExecute___024root___eval_static(VExecute___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VExecute__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VExecute___024root___eval_static\n"); );
}

VL_ATTR_COLD void VExecute___024root___eval_initial(VExecute___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VExecute__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VExecute___024root___eval_initial\n"); );
}

VL_ATTR_COLD void VExecute___024root___eval_final(VExecute___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VExecute__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VExecute___024root___eval_final\n"); );
}

VL_ATTR_COLD void VExecute___024root___eval_triggers__stl(VExecute___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void VExecute___024root___dump_triggers__stl(VExecute___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD void VExecute___024root___eval_stl(VExecute___024root* vlSelf);

VL_ATTR_COLD void VExecute___024root___eval_settle(VExecute___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VExecute__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VExecute___024root___eval_settle\n"); );
    // Init
    CData/*0:0*/ __VstlContinue;
    // Body
    vlSelf->__VstlIterCount = 0U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        __VstlContinue = 0U;
        VExecute___024root___eval_triggers__stl(vlSelf);
        if (vlSelf->__VstlTriggered.any()) {
            __VstlContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VstlIterCount))) {
#ifdef VL_DEBUG
                VExecute___024root___dump_triggers__stl(vlSelf);
#endif
                VL_FATAL_MT("Execute.sv", 61, "", "Settle region did not converge.");
            }
            vlSelf->__VstlIterCount = ((IData)(1U) 
                                       + vlSelf->__VstlIterCount);
            VExecute___024root___eval_stl(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VExecute___024root___dump_triggers__stl(VExecute___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VExecute__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VExecute___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VstlTriggered.at(0U)) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

void VExecute___024root___ico_sequent__TOP__0(VExecute___024root* vlSelf);

VL_ATTR_COLD void VExecute___024root___eval_stl(VExecute___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VExecute__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VExecute___024root___eval_stl\n"); );
    // Body
    if (vlSelf->__VstlTriggered.at(0U)) {
        VExecute___024root___ico_sequent__TOP__0(vlSelf);
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VExecute___024root___dump_triggers__ico(VExecute___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VExecute__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VExecute___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VicoTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VicoTriggered.at(0U)) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void VExecute___024root___dump_triggers__act(VExecute___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VExecute__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VExecute___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void VExecute___024root___dump_triggers__nba(VExecute___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VExecute__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VExecute___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void VExecute___024root___ctor_var_reset(VExecute___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VExecute__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VExecute___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clock = VL_RAND_RESET_I(1);
    vlSelf->reset = VL_RAND_RESET_I(1);
    vlSelf->io_instruction = VL_RAND_RESET_I(32);
    vlSelf->io_instruction_address = VL_RAND_RESET_I(32);
    vlSelf->io_reg1_data = VL_RAND_RESET_I(32);
    vlSelf->io_reg2_data = VL_RAND_RESET_I(32);
    vlSelf->io_immediate = VL_RAND_RESET_I(32);
    vlSelf->io_aluop1_source = VL_RAND_RESET_I(1);
    vlSelf->io_aluop2_source = VL_RAND_RESET_I(1);
    vlSelf->io_mem_alu_result = VL_RAND_RESET_I(32);
    vlSelf->io_if_jump_flag = VL_RAND_RESET_I(1);
    vlSelf->io_if_jump_address = VL_RAND_RESET_I(32);
}

VL_ATTR_COLD void VExecute___024root___configure_coverage(VExecute___024root* vlSelf, bool first) {
    if (false && vlSelf) {}  // Prevent unused
    VExecute__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VExecute___024root___configure_coverage\n"); );
    // Body
    if (false && first) {}  // Prevent unused
}
