// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VInstructionFetch.h for the primary calling header

#include "verilated.h"

#include "VInstructionFetch___024root.h"

VL_ATTR_COLD void VInstructionFetch___024root___eval_static(VInstructionFetch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionFetch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionFetch___024root___eval_static\n"); );
}

VL_ATTR_COLD void VInstructionFetch___024root___eval_initial(VInstructionFetch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionFetch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionFetch___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vtrigrprev__TOP__clock = vlSelf->clock;
}

VL_ATTR_COLD void VInstructionFetch___024root___eval_final(VInstructionFetch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionFetch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionFetch___024root___eval_final\n"); );
}

VL_ATTR_COLD void VInstructionFetch___024root___eval_triggers__stl(VInstructionFetch___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void VInstructionFetch___024root___dump_triggers__stl(VInstructionFetch___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD void VInstructionFetch___024root___eval_stl(VInstructionFetch___024root* vlSelf);

VL_ATTR_COLD void VInstructionFetch___024root___eval_settle(VInstructionFetch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionFetch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionFetch___024root___eval_settle\n"); );
    // Init
    CData/*0:0*/ __VstlContinue;
    // Body
    vlSelf->__VstlIterCount = 0U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        __VstlContinue = 0U;
        VInstructionFetch___024root___eval_triggers__stl(vlSelf);
        if (vlSelf->__VstlTriggered.any()) {
            __VstlContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VstlIterCount))) {
#ifdef VL_DEBUG
                VInstructionFetch___024root___dump_triggers__stl(vlSelf);
#endif
                VL_FATAL_MT("InstructionFetch.sv", 1, "", "Settle region did not converge.");
            }
            vlSelf->__VstlIterCount = ((IData)(1U) 
                                       + vlSelf->__VstlIterCount);
            VInstructionFetch___024root___eval_stl(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VInstructionFetch___024root___dump_triggers__stl(VInstructionFetch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionFetch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionFetch___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VstlTriggered.at(0U)) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void VInstructionFetch___024root___stl_sequent__TOP__0(VInstructionFetch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionFetch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionFetch___024root___stl_sequent__TOP__0\n"); );
    // Body
    vlSelf->io_instruction_address = vlSelf->InstructionFetch__DOT__pc;
    vlSelf->InstructionFetch__DOT___pc_T_1 = ((IData)(4U) 
                                              + vlSelf->InstructionFetch__DOT__pc);
    vlSelf->io_instruction = ((IData)(vlSelf->io_instruction_valid)
                               ? vlSelf->io_instruction_read_data
                               : 0x13U);
}

VL_ATTR_COLD void VInstructionFetch___024root___eval_stl(VInstructionFetch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionFetch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionFetch___024root___eval_stl\n"); );
    // Body
    if (vlSelf->__VstlTriggered.at(0U)) {
        VInstructionFetch___024root___stl_sequent__TOP__0(vlSelf);
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VInstructionFetch___024root___dump_triggers__ico(VInstructionFetch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionFetch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionFetch___024root___dump_triggers__ico\n"); );
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
VL_ATTR_COLD void VInstructionFetch___024root___dump_triggers__act(VInstructionFetch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionFetch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionFetch___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VactTriggered.at(0U)) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clock)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void VInstructionFetch___024root___dump_triggers__nba(VInstructionFetch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionFetch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionFetch___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VnbaTriggered.at(0U)) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clock)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void VInstructionFetch___024root___ctor_var_reset(VInstructionFetch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionFetch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionFetch___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clock = VL_RAND_RESET_I(1);
    vlSelf->reset = VL_RAND_RESET_I(1);
    vlSelf->io_jump_flag_id = VL_RAND_RESET_I(1);
    vlSelf->io_jump_address_id = VL_RAND_RESET_I(32);
    vlSelf->io_instruction_read_data = VL_RAND_RESET_I(32);
    vlSelf->io_instruction_valid = VL_RAND_RESET_I(1);
    vlSelf->io_instruction_address = VL_RAND_RESET_I(32);
    vlSelf->io_instruction = VL_RAND_RESET_I(32);
    vlSelf->InstructionFetch__DOT__pc = VL_RAND_RESET_I(32);
    vlSelf->InstructionFetch__DOT___pc_T_1 = VL_RAND_RESET_I(32);
    vlSelf->__Vtrigrprev__TOP__clock = VL_RAND_RESET_I(1);
}

VL_ATTR_COLD void VInstructionFetch___024root___configure_coverage(VInstructionFetch___024root* vlSelf, bool first) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionFetch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionFetch___024root___configure_coverage\n"); );
    // Body
    if (false && first) {}  // Prevent unused
}
