// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VInstructionDecode.h for the primary calling header

#include "verilated.h"

#include "VInstructionDecode___024root.h"

VL_INLINE_OPT void VInstructionDecode___024root___ico_sequent__TOP__0(VInstructionDecode___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionDecode__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionDecode___024root___ico_sequent__TOP__0\n"); );
    // Init
    IData/*31:0*/ InstructionDecode__DOT___immediate_T_9;
    InstructionDecode__DOT___immediate_T_9 = 0;
    CData/*0:0*/ InstructionDecode__DOT____VdfgTmp_h63924a1c__0;
    InstructionDecode__DOT____VdfgTmp_h63924a1c__0 = 0;
    // Body
    vlSelf->io_regs_reg1_read_address = ((0x37U == 
                                          (0x7fU & vlSelf->io_instruction))
                                          ? 0U : (0x1fU 
                                                  & (vlSelf->io_instruction 
                                                     >> 0xfU)));
    vlSelf->io_regs_reg2_read_address = (0x1fU & (vlSelf->io_instruction 
                                                  >> 0x14U));
    vlSelf->io_ex_aluop1_source = ((0x17U == (0x7fU 
                                              & vlSelf->io_instruction)) 
                                   | ((0x63U == (0x7fU 
                                                 & vlSelf->io_instruction)) 
                                      | (0x6fU == (0x7fU 
                                                   & vlSelf->io_instruction))));
    vlSelf->io_reg_write_address = (0x1fU & (vlSelf->io_instruction 
                                             >> 7U));
    InstructionDecode__DOT___immediate_T_9 = ((((vlSelf->io_instruction 
                                                 >> 0x1fU)
                                                 ? 0x1fffffU
                                                 : 0U) 
                                               << 0xbU) 
                                              | (0x7ffU 
                                                 & (vlSelf->io_instruction 
                                                    >> 0x14U)));
    vlSelf->io_memory_write_enable = (0x23U == (0x7fU 
                                                & vlSelf->io_instruction));
    InstructionDecode__DOT____VdfgTmp_h63924a1c__0 
        = ((0x17U == (0x7fU & vlSelf->io_instruction)) 
           | ((0x37U == (0x7fU & vlSelf->io_instruction)) 
              | (0x6fU == (0x7fU & vlSelf->io_instruction))));
    vlSelf->io_memory_read_enable = (3U == (0x7fU & vlSelf->io_instruction));
    vlSelf->io_ex_aluop2_source = ((IData)(vlSelf->io_memory_write_enable) 
                                   | ((0x13U == (0x7fU 
                                                 & vlSelf->io_instruction)) 
                                      | ((IData)(vlSelf->io_memory_read_enable) 
                                         | ((0x67U 
                                             == (0x7fU 
                                                 & vlSelf->io_instruction)) 
                                            | (IData)(InstructionDecode__DOT____VdfgTmp_h63924a1c__0)))));
    vlSelf->io_ex_immediate = ((0x6fU == (0x7fU & vlSelf->io_instruction))
                                ? ((((vlSelf->io_instruction 
                                      >> 0x1fU) ? 0xfffU
                                      : 0U) << 0x14U) 
                                   | ((0xff000U & vlSelf->io_instruction) 
                                      | ((0x800U & 
                                          (vlSelf->io_instruction 
                                           >> 9U)) 
                                         | (0x7feU 
                                            & (vlSelf->io_instruction 
                                               >> 0x14U)))))
                                : ((0x17U == (0x7fU 
                                              & vlSelf->io_instruction))
                                    ? (0xfffff000U 
                                       & vlSelf->io_instruction)
                                    : ((0x37U == (0x7fU 
                                                  & vlSelf->io_instruction))
                                        ? (0xfffff000U 
                                           & vlSelf->io_instruction)
                                        : ((0x63U == 
                                            (0x7fU 
                                             & vlSelf->io_instruction))
                                            ? ((((vlSelf->io_instruction 
                                                  >> 0x1fU)
                                                  ? 0xfffffU
                                                  : 0U) 
                                                << 0xcU) 
                                               | ((0x800U 
                                                   & (vlSelf->io_instruction 
                                                      << 4U)) 
                                                  | ((0x7e0U 
                                                      & (vlSelf->io_instruction 
                                                         >> 0x14U)) 
                                                     | (0x1eU 
                                                        & (vlSelf->io_instruction 
                                                           >> 7U)))))
                                            : ((IData)(vlSelf->io_memory_write_enable)
                                                ? (
                                                   (((vlSelf->io_instruction 
                                                      >> 0x1fU)
                                                      ? 0x1fffffU
                                                      : 0U) 
                                                    << 0xbU) 
                                                   | ((0x7e0U 
                                                       & (vlSelf->io_instruction 
                                                          >> 0x14U)) 
                                                      | (IData)(vlSelf->io_reg_write_address)))
                                                : (
                                                   (0x67U 
                                                    == 
                                                    (0x7fU 
                                                     & vlSelf->io_instruction))
                                                    ? InstructionDecode__DOT___immediate_T_9
                                                    : 
                                                   ((IData)(vlSelf->io_memory_read_enable)
                                                     ? InstructionDecode__DOT___immediate_T_9
                                                     : 
                                                    ((0x13U 
                                                      == 
                                                      (0x7fU 
                                                       & vlSelf->io_instruction))
                                                      ? InstructionDecode__DOT___immediate_T_9
                                                      : 
                                                     ((((vlSelf->io_instruction 
                                                         >> 0x1fU)
                                                         ? 0xfffffU
                                                         : 0U) 
                                                       << 0xcU) 
                                                      | (vlSelf->io_instruction 
                                                         >> 0x14U))))))))));
    vlSelf->io_reg_write_enable = ((0x33U == (0x7fU 
                                              & vlSelf->io_instruction)) 
                                   | ((0x13U == (0x7fU 
                                                 & vlSelf->io_instruction)) 
                                      | ((IData)(vlSelf->io_memory_read_enable) 
                                         | ((IData)(InstructionDecode__DOT____VdfgTmp_h63924a1c__0) 
                                            | (0x67U 
                                               == (0x7fU 
                                                   & vlSelf->io_instruction))))));
    vlSelf->io_wb_reg_write_source = ((IData)(vlSelf->io_reg_write_enable)
                                       ? 0U : 1U);
}

void VInstructionDecode___024root___eval_ico(VInstructionDecode___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionDecode__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionDecode___024root___eval_ico\n"); );
    // Body
    if (vlSelf->__VicoTriggered.at(0U)) {
        VInstructionDecode___024root___ico_sequent__TOP__0(vlSelf);
    }
}

void VInstructionDecode___024root___eval_act(VInstructionDecode___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionDecode__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionDecode___024root___eval_act\n"); );
}

void VInstructionDecode___024root___eval_nba(VInstructionDecode___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionDecode__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionDecode___024root___eval_nba\n"); );
}

void VInstructionDecode___024root___eval_triggers__ico(VInstructionDecode___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void VInstructionDecode___024root___dump_triggers__ico(VInstructionDecode___024root* vlSelf);
#endif  // VL_DEBUG
void VInstructionDecode___024root___eval_triggers__act(VInstructionDecode___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void VInstructionDecode___024root___dump_triggers__act(VInstructionDecode___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void VInstructionDecode___024root___dump_triggers__nba(VInstructionDecode___024root* vlSelf);
#endif  // VL_DEBUG

void VInstructionDecode___024root___eval(VInstructionDecode___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionDecode__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionDecode___024root___eval\n"); );
    // Init
    CData/*0:0*/ __VicoContinue;
    VlTriggerVec<0> __VpreTriggered;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    vlSelf->__VicoIterCount = 0U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        __VicoContinue = 0U;
        VInstructionDecode___024root___eval_triggers__ico(vlSelf);
        if (vlSelf->__VicoTriggered.any()) {
            __VicoContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VicoIterCount))) {
#ifdef VL_DEBUG
                VInstructionDecode___024root___dump_triggers__ico(vlSelf);
#endif
                VL_FATAL_MT("InstructionDecode.sv", 1, "", "Input combinational region did not converge.");
            }
            vlSelf->__VicoIterCount = ((IData)(1U) 
                                       + vlSelf->__VicoIterCount);
            VInstructionDecode___024root___eval_ico(vlSelf);
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
            VInstructionDecode___024root___eval_triggers__act(vlSelf);
            if (vlSelf->__VactTriggered.any()) {
                vlSelf->__VactContinue = 1U;
                if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                    VInstructionDecode___024root___dump_triggers__act(vlSelf);
#endif
                    VL_FATAL_MT("InstructionDecode.sv", 1, "", "Active region did not converge.");
                }
                vlSelf->__VactIterCount = ((IData)(1U) 
                                           + vlSelf->__VactIterCount);
                __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
                vlSelf->__VnbaTriggered.set(vlSelf->__VactTriggered);
                VInstructionDecode___024root___eval_act(vlSelf);
            }
        }
        if (vlSelf->__VnbaTriggered.any()) {
            __VnbaContinue = 1U;
            if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
                VInstructionDecode___024root___dump_triggers__nba(vlSelf);
#endif
                VL_FATAL_MT("InstructionDecode.sv", 1, "", "NBA region did not converge.");
            }
            __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
            VInstructionDecode___024root___eval_nba(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
void VInstructionDecode___024root___eval_debug_assertions(VInstructionDecode___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VInstructionDecode__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VInstructionDecode___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clock & 0xfeU))) {
        Verilated::overWidthError("clock");}
    if (VL_UNLIKELY((vlSelf->reset & 0xfeU))) {
        Verilated::overWidthError("reset");}
}
#endif  // VL_DEBUG
