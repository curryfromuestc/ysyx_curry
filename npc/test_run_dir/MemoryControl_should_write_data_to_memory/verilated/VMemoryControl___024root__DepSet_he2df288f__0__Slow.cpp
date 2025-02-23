// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VMemoryControl.h for the primary calling header

#include "verilated.h"

#include "VMemoryControl___024root.h"

VL_ATTR_COLD void VMemoryControl___024root___eval_static(VMemoryControl___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VMemoryControl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMemoryControl___024root___eval_static\n"); );
}

VL_ATTR_COLD void VMemoryControl___024root___eval_initial(VMemoryControl___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VMemoryControl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMemoryControl___024root___eval_initial\n"); );
}

VL_ATTR_COLD void VMemoryControl___024root___eval_final(VMemoryControl___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VMemoryControl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMemoryControl___024root___eval_final\n"); );
}

VL_ATTR_COLD void VMemoryControl___024root___eval_triggers__stl(VMemoryControl___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void VMemoryControl___024root___dump_triggers__stl(VMemoryControl___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD void VMemoryControl___024root___eval_stl(VMemoryControl___024root* vlSelf);

VL_ATTR_COLD void VMemoryControl___024root___eval_settle(VMemoryControl___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VMemoryControl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMemoryControl___024root___eval_settle\n"); );
    // Init
    CData/*0:0*/ __VstlContinue;
    // Body
    vlSelf->__VstlIterCount = 0U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        __VstlContinue = 0U;
        VMemoryControl___024root___eval_triggers__stl(vlSelf);
        if (vlSelf->__VstlTriggered.any()) {
            __VstlContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VstlIterCount))) {
#ifdef VL_DEBUG
                VMemoryControl___024root___dump_triggers__stl(vlSelf);
#endif
                VL_FATAL_MT("MemoryControl.sv", 1, "", "Settle region did not converge.");
            }
            vlSelf->__VstlIterCount = ((IData)(1U) 
                                       + vlSelf->__VstlIterCount);
            VMemoryControl___024root___eval_stl(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VMemoryControl___024root___dump_triggers__stl(VMemoryControl___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VMemoryControl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMemoryControl___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VstlTriggered.at(0U)) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

void VMemoryControl___024root___ico_sequent__TOP__0(VMemoryControl___024root* vlSelf);

VL_ATTR_COLD void VMemoryControl___024root___eval_stl(VMemoryControl___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VMemoryControl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMemoryControl___024root___eval_stl\n"); );
    // Body
    if (vlSelf->__VstlTriggered.at(0U)) {
        VMemoryControl___024root___ico_sequent__TOP__0(vlSelf);
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VMemoryControl___024root___dump_triggers__ico(VMemoryControl___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VMemoryControl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMemoryControl___024root___dump_triggers__ico\n"); );
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
VL_ATTR_COLD void VMemoryControl___024root___dump_triggers__act(VMemoryControl___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VMemoryControl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMemoryControl___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void VMemoryControl___024root___dump_triggers__nba(VMemoryControl___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VMemoryControl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMemoryControl___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void VMemoryControl___024root___ctor_var_reset(VMemoryControl___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VMemoryControl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMemoryControl___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clock = VL_RAND_RESET_I(1);
    vlSelf->reset = VL_RAND_RESET_I(1);
    vlSelf->io_alu_result = VL_RAND_RESET_I(32);
    vlSelf->io_reg2_data = VL_RAND_RESET_I(32);
    vlSelf->io_memory_read_enable = VL_RAND_RESET_I(1);
    vlSelf->io_memory_write_enable = VL_RAND_RESET_I(1);
    vlSelf->io_funct3 = VL_RAND_RESET_I(3);
    vlSelf->io_wb_memory_read_data = VL_RAND_RESET_I(32);
    vlSelf->io_memory_bundle_address = VL_RAND_RESET_I(32);
    vlSelf->io_memory_bundle_read_data = VL_RAND_RESET_I(32);
    vlSelf->io_memory_bundle_write_data = VL_RAND_RESET_I(32);
    vlSelf->io_memory_bundle_write_enable = VL_RAND_RESET_I(1);
    vlSelf->io_memory_bundle_write_strobe_0 = VL_RAND_RESET_I(1);
    vlSelf->io_memory_bundle_write_strobe_1 = VL_RAND_RESET_I(1);
    vlSelf->io_memory_bundle_write_strobe_2 = VL_RAND_RESET_I(1);
    vlSelf->io_memory_bundle_write_strobe_3 = VL_RAND_RESET_I(1);
}

VL_ATTR_COLD void VMemoryControl___024root___configure_coverage(VMemoryControl___024root* vlSelf, bool first) {
    if (false && vlSelf) {}  // Prevent unused
    VMemoryControl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMemoryControl___024root___configure_coverage\n"); );
    // Body
    if (false && first) {}  // Prevent unused
}
