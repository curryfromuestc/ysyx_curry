// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VInstructionFetch.h for the primary calling header

#include "verilated.h"

#include "VInstructionFetch___024root.h"

VL_INLINE_OPT void VInstructionFetch___024root___ico_sequent__TOP__0(VInstructionFetch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionFetch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionFetch___024root___ico_sequent__TOP__0\n"); );
    // Body
    vlSelf->io_instruction = ((IData)(vlSelf->io_instruction_valid)
                               ? vlSelf->io_instruction_read_data
                               : 0x13U);
}

void VInstructionFetch___024root___eval_ico(VInstructionFetch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionFetch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionFetch___024root___eval_ico\n"); );
    // Body
    if (vlSelf->__VicoTriggered.at(0U)) {
        VInstructionFetch___024root___ico_sequent__TOP__0(vlSelf);
    }
}

void VInstructionFetch___024root___eval_act(VInstructionFetch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionFetch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionFetch___024root___eval_act\n"); );
}

VL_INLINE_OPT void VInstructionFetch___024root___nba_sequent__TOP__0(VInstructionFetch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionFetch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionFetch___024root___nba_sequent__TOP__0\n"); );
    // Body
    if (vlSelf->reset) {
        vlSelf->InstructionFetch__DOT__pc = 0x80000000U;
    } else if (vlSelf->io_instruction_valid) {
        vlSelf->InstructionFetch__DOT__pc = ((IData)(vlSelf->io_jump_flag_id)
                                              ? vlSelf->io_jump_address_id
                                              : vlSelf->InstructionFetch__DOT___pc_T_1);
    }
    vlSelf->io_instruction_address = vlSelf->InstructionFetch__DOT__pc;
    vlSelf->InstructionFetch__DOT___pc_T_1 = ((IData)(4U) 
                                              + vlSelf->InstructionFetch__DOT__pc);
}

void VInstructionFetch___024root___eval_nba(VInstructionFetch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionFetch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionFetch___024root___eval_nba\n"); );
    // Body
    if (vlSelf->__VnbaTriggered.at(0U)) {
        VInstructionFetch___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void VInstructionFetch___024root___eval_triggers__ico(VInstructionFetch___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void VInstructionFetch___024root___dump_triggers__ico(VInstructionFetch___024root* vlSelf);
#endif  // VL_DEBUG
void VInstructionFetch___024root___eval_triggers__act(VInstructionFetch___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void VInstructionFetch___024root___dump_triggers__act(VInstructionFetch___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void VInstructionFetch___024root___dump_triggers__nba(VInstructionFetch___024root* vlSelf);
#endif  // VL_DEBUG

void VInstructionFetch___024root___eval(VInstructionFetch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionFetch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionFetch___024root___eval\n"); );
    // Init
    CData/*0:0*/ __VicoContinue;
    VlTriggerVec<1> __VpreTriggered;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    vlSelf->__VicoIterCount = 0U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        __VicoContinue = 0U;
        VInstructionFetch___024root___eval_triggers__ico(vlSelf);
        if (vlSelf->__VicoTriggered.any()) {
            __VicoContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VicoIterCount))) {
#ifdef VL_DEBUG
                VInstructionFetch___024root___dump_triggers__ico(vlSelf);
#endif
                VL_FATAL_MT("InstructionFetch.sv", 1, "", "Input combinational region did not converge.");
            }
            vlSelf->__VicoIterCount = ((IData)(1U) 
                                       + vlSelf->__VicoIterCount);
            VInstructionFetch___024root___eval_ico(vlSelf);
        }
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        __VnbaContinue = 0U;
        vlSelf->__VnbaTriggered.clear();
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            vlSelf->__VactContinue = 0U;
            VInstructionFetch___024root___eval_triggers__act(vlSelf);
            if (vlSelf->__VactTriggered.any()) {
                vlSelf->__VactContinue = 1U;
                if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                    VInstructionFetch___024root___dump_triggers__act(vlSelf);
#endif
                    VL_FATAL_MT("InstructionFetch.sv", 1, "", "Active region did not converge.");
                }
                vlSelf->__VactIterCount = ((IData)(1U) 
                                           + vlSelf->__VactIterCount);
                __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
                vlSelf->__VnbaTriggered.set(vlSelf->__VactTriggered);
                VInstructionFetch___024root___eval_act(vlSelf);
            }
        }
        if (vlSelf->__VnbaTriggered.any()) {
            __VnbaContinue = 1U;
            if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
                VInstructionFetch___024root___dump_triggers__nba(vlSelf);
#endif
                VL_FATAL_MT("InstructionFetch.sv", 1, "", "NBA region did not converge.");
            }
            __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
            VInstructionFetch___024root___eval_nba(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
void VInstructionFetch___024root___eval_debug_assertions(VInstructionFetch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionFetch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionFetch___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clock & 0xfeU))) {
        Verilated::overWidthError("clock");}
    if (VL_UNLIKELY((vlSelf->reset & 0xfeU))) {
        Verilated::overWidthError("reset");}
    if (VL_UNLIKELY((vlSelf->io_jump_flag_id & 0xfeU))) {
        Verilated::overWidthError("io_jump_flag_id");}
    if (VL_UNLIKELY((vlSelf->io_instruction_valid & 0xfeU))) {
        Verilated::overWidthError("io_instruction_valid");}
}
#endif  // VL_DEBUG
