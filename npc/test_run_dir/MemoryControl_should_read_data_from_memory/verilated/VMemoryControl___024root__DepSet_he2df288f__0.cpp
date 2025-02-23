// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VMemoryControl.h for the primary calling header

#include "verilated.h"

#include "VMemoryControl___024root.h"

VL_INLINE_OPT void VMemoryControl___024root___ico_sequent__TOP__0(VMemoryControl___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VMemoryControl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMemoryControl___024root___ico_sequent__TOP__0\n"); );
    // Init
    CData/*0:0*/ MemoryControl__DOT___GEN_13;
    MemoryControl__DOT___GEN_13 = 0;
    CData/*0:0*/ MemoryControl__DOT___GEN_16;
    MemoryControl__DOT___GEN_16 = 0;
    // Body
    vlSelf->io_memory_bundle_address = vlSelf->io_alu_result;
    vlSelf->io_memory_bundle_write_enable = ((~ (IData)(vlSelf->io_memory_read_enable)) 
                                             & (IData)(vlSelf->io_memory_write_enable));
    if (vlSelf->io_memory_read_enable) {
        vlSelf->io_wb_memory_read_data = ((2U == (IData)(vlSelf->io_funct3))
                                           ? vlSelf->io_memory_bundle_read_data
                                           : ((5U == (IData)(vlSelf->io_funct3))
                                               ? ((0U 
                                                   == 
                                                   (3U 
                                                    & vlSelf->io_alu_result))
                                                   ? 
                                                  (0xffffU 
                                                   & vlSelf->io_memory_bundle_read_data)
                                                   : 
                                                  (vlSelf->io_memory_bundle_read_data 
                                                   >> 0x10U))
                                               : ((1U 
                                                   == (IData)(vlSelf->io_funct3))
                                                   ? 
                                                  ((0U 
                                                    == 
                                                    (3U 
                                                     & vlSelf->io_alu_result))
                                                    ? 
                                                   ((((0x8000U 
                                                       & vlSelf->io_memory_bundle_read_data)
                                                       ? 0xffffU
                                                       : 0U) 
                                                     << 0x10U) 
                                                    | (0xffffU 
                                                       & vlSelf->io_memory_bundle_read_data))
                                                    : 
                                                   ((((vlSelf->io_memory_bundle_read_data 
                                                       >> 0x1fU)
                                                       ? 0xffffU
                                                       : 0U) 
                                                     << 0x10U) 
                                                    | (vlSelf->io_memory_bundle_read_data 
                                                       >> 0x10U)))
                                                   : 
                                                  ((4U 
                                                    == (IData)(vlSelf->io_funct3))
                                                    ? 
                                                   ((2U 
                                                     == 
                                                     (3U 
                                                      & vlSelf->io_alu_result))
                                                     ? 
                                                    (0xffU 
                                                     & (vlSelf->io_memory_bundle_read_data 
                                                        >> 0x10U))
                                                     : 
                                                    ((1U 
                                                      == 
                                                      (3U 
                                                       & vlSelf->io_alu_result))
                                                      ? 
                                                     (0xffU 
                                                      & (vlSelf->io_memory_bundle_read_data 
                                                         >> 8U))
                                                      : 
                                                     ((0U 
                                                       == 
                                                       (3U 
                                                        & vlSelf->io_alu_result))
                                                       ? 
                                                      (0xffU 
                                                       & vlSelf->io_memory_bundle_read_data)
                                                       : 
                                                      (vlSelf->io_memory_bundle_read_data 
                                                       >> 0x18U))))
                                                    : 
                                                   ((0U 
                                                     == (IData)(vlSelf->io_funct3))
                                                     ? 
                                                    ((2U 
                                                      == 
                                                      (3U 
                                                       & vlSelf->io_alu_result))
                                                      ? 
                                                     ((((0x800000U 
                                                         & vlSelf->io_memory_bundle_read_data)
                                                         ? 0xffffffU
                                                         : 0U) 
                                                       << 8U) 
                                                      | (0xffU 
                                                         & (vlSelf->io_memory_bundle_read_data 
                                                            >> 0x10U)))
                                                      : 
                                                     ((1U 
                                                       == 
                                                       (3U 
                                                        & vlSelf->io_alu_result))
                                                       ? 
                                                      ((((0x8000U 
                                                          & vlSelf->io_memory_bundle_read_data)
                                                          ? 0xffffffU
                                                          : 0U) 
                                                        << 8U) 
                                                       | (0xffU 
                                                          & (vlSelf->io_memory_bundle_read_data 
                                                             >> 8U)))
                                                       : 
                                                      ((0U 
                                                        == 
                                                        (3U 
                                                         & vlSelf->io_alu_result))
                                                        ? 
                                                       ((((0x80U 
                                                           & vlSelf->io_memory_bundle_read_data)
                                                           ? 0xffffffU
                                                           : 0U) 
                                                         << 8U) 
                                                        | (0xffU 
                                                           & vlSelf->io_memory_bundle_read_data))
                                                        : 
                                                       ((((vlSelf->io_memory_bundle_read_data 
                                                           >> 0x1fU)
                                                           ? 0xffffffU
                                                           : 0U) 
                                                         << 8U) 
                                                        | (vlSelf->io_memory_bundle_read_data 
                                                           >> 0x18U)))))
                                                     : 0U)))));
        vlSelf->io_memory_bundle_write_data = 0U;
    } else {
        vlSelf->io_wb_memory_read_data = 0U;
        vlSelf->io_memory_bundle_write_data = ((IData)(vlSelf->io_memory_write_enable)
                                                ? (IData)(
                                                          (0xffffffffffULL 
                                                           & ((0U 
                                                               == (IData)(vlSelf->io_funct3))
                                                               ? 
                                                              ((QData)((IData)(
                                                                               (0x1ffU 
                                                                                & vlSelf->io_reg2_data))) 
                                                               << 
                                                               (0x18U 
                                                                & (vlSelf->io_alu_result 
                                                                   << 3U)))
                                                               : 
                                                              ((1U 
                                                                == (IData)(vlSelf->io_funct3))
                                                                ? 
                                                               ((0U 
                                                                 == 
                                                                 (3U 
                                                                  & vlSelf->io_alu_result))
                                                                 ? (QData)((IData)(
                                                                                (0x1ffffU 
                                                                                & vlSelf->io_reg2_data)))
                                                                 : 
                                                                ((QData)((IData)(
                                                                                (0x1ffffU 
                                                                                & vlSelf->io_reg2_data))) 
                                                                 << 0x10U))
                                                                : (QData)((IData)(vlSelf->io_reg2_data))))))
                                                : 0U);
    }
    if ((1U == (IData)(vlSelf->io_funct3))) {
        MemoryControl__DOT___GEN_13 = (0U == (3U & vlSelf->io_alu_result));
        MemoryControl__DOT___GEN_16 = (0U != (3U & vlSelf->io_alu_result));
    } else {
        MemoryControl__DOT___GEN_13 = (2U == (IData)(vlSelf->io_funct3));
        MemoryControl__DOT___GEN_16 = (2U == (IData)(vlSelf->io_funct3));
    }
    vlSelf->io_memory_bundle_write_strobe_0 = ((~ (IData)(vlSelf->io_memory_read_enable)) 
                                               & ((IData)(vlSelf->io_memory_write_enable) 
                                                  & ((0U 
                                                      == (IData)(vlSelf->io_funct3))
                                                      ? 
                                                     (0U 
                                                      == 
                                                      (3U 
                                                       & vlSelf->io_alu_result))
                                                      : (IData)(MemoryControl__DOT___GEN_13))));
    vlSelf->io_memory_bundle_write_strobe_1 = ((~ (IData)(vlSelf->io_memory_read_enable)) 
                                               & ((IData)(vlSelf->io_memory_write_enable) 
                                                  & ((0U 
                                                      == (IData)(vlSelf->io_funct3))
                                                      ? 
                                                     (1U 
                                                      == 
                                                      (3U 
                                                       & vlSelf->io_alu_result))
                                                      : (IData)(MemoryControl__DOT___GEN_13))));
    vlSelf->io_memory_bundle_write_strobe_2 = ((~ (IData)(vlSelf->io_memory_read_enable)) 
                                               & ((IData)(vlSelf->io_memory_write_enable) 
                                                  & ((0U 
                                                      == (IData)(vlSelf->io_funct3))
                                                      ? 
                                                     (2U 
                                                      == 
                                                      (3U 
                                                       & vlSelf->io_alu_result))
                                                      : (IData)(MemoryControl__DOT___GEN_16))));
    vlSelf->io_memory_bundle_write_strobe_3 = ((~ (IData)(vlSelf->io_memory_read_enable)) 
                                               & ((IData)(vlSelf->io_memory_write_enable) 
                                                  & ((0U 
                                                      == (IData)(vlSelf->io_funct3))
                                                      ? 
                                                     (3U 
                                                      == 
                                                      (3U 
                                                       & vlSelf->io_alu_result))
                                                      : (IData)(MemoryControl__DOT___GEN_16))));
}

void VMemoryControl___024root___eval_ico(VMemoryControl___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VMemoryControl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMemoryControl___024root___eval_ico\n"); );
    // Body
    if (vlSelf->__VicoTriggered.at(0U)) {
        VMemoryControl___024root___ico_sequent__TOP__0(vlSelf);
    }
}

void VMemoryControl___024root___eval_act(VMemoryControl___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VMemoryControl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMemoryControl___024root___eval_act\n"); );
}

void VMemoryControl___024root___eval_nba(VMemoryControl___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VMemoryControl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMemoryControl___024root___eval_nba\n"); );
}

void VMemoryControl___024root___eval_triggers__ico(VMemoryControl___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void VMemoryControl___024root___dump_triggers__ico(VMemoryControl___024root* vlSelf);
#endif  // VL_DEBUG
void VMemoryControl___024root___eval_triggers__act(VMemoryControl___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void VMemoryControl___024root___dump_triggers__act(VMemoryControl___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void VMemoryControl___024root___dump_triggers__nba(VMemoryControl___024root* vlSelf);
#endif  // VL_DEBUG

void VMemoryControl___024root___eval(VMemoryControl___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VMemoryControl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMemoryControl___024root___eval\n"); );
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
        VMemoryControl___024root___eval_triggers__ico(vlSelf);
        if (vlSelf->__VicoTriggered.any()) {
            __VicoContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VicoIterCount))) {
#ifdef VL_DEBUG
                VMemoryControl___024root___dump_triggers__ico(vlSelf);
#endif
                VL_FATAL_MT("MemoryControl.sv", 1, "", "Input combinational region did not converge.");
            }
            vlSelf->__VicoIterCount = ((IData)(1U) 
                                       + vlSelf->__VicoIterCount);
            VMemoryControl___024root___eval_ico(vlSelf);
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
            VMemoryControl___024root___eval_triggers__act(vlSelf);
            if (vlSelf->__VactTriggered.any()) {
                vlSelf->__VactContinue = 1U;
                if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                    VMemoryControl___024root___dump_triggers__act(vlSelf);
#endif
                    VL_FATAL_MT("MemoryControl.sv", 1, "", "Active region did not converge.");
                }
                vlSelf->__VactIterCount = ((IData)(1U) 
                                           + vlSelf->__VactIterCount);
                __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
                vlSelf->__VnbaTriggered.set(vlSelf->__VactTriggered);
                VMemoryControl___024root___eval_act(vlSelf);
            }
        }
        if (vlSelf->__VnbaTriggered.any()) {
            __VnbaContinue = 1U;
            if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
                VMemoryControl___024root___dump_triggers__nba(vlSelf);
#endif
                VL_FATAL_MT("MemoryControl.sv", 1, "", "NBA region did not converge.");
            }
            __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
            VMemoryControl___024root___eval_nba(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
void VMemoryControl___024root___eval_debug_assertions(VMemoryControl___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VMemoryControl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMemoryControl___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clock & 0xfeU))) {
        Verilated::overWidthError("clock");}
    if (VL_UNLIKELY((vlSelf->reset & 0xfeU))) {
        Verilated::overWidthError("reset");}
    if (VL_UNLIKELY((vlSelf->io_memory_read_enable 
                     & 0xfeU))) {
        Verilated::overWidthError("io_memory_read_enable");}
    if (VL_UNLIKELY((vlSelf->io_memory_write_enable 
                     & 0xfeU))) {
        Verilated::overWidthError("io_memory_write_enable");}
    if (VL_UNLIKELY((vlSelf->io_funct3 & 0xf8U))) {
        Verilated::overWidthError("io_funct3");}
}
#endif  // VL_DEBUG
