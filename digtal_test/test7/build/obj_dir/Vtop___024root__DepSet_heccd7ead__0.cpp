// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"

#include "Vtop___024root.h"

void Vtop___024root___eval_act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_act\n"); );
}

extern const VlUnpacked<CData/*7:0*/, 16> Vtop__ConstPool__TABLE_h1f93ebb4_0;
extern const VlUnpacked<CData/*7:0*/, 256> Vtop__ConstPool__TABLE_h181586bb_0;

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    // Init
    CData/*7:0*/ top__DOT__tmp_data;
    top__DOT__tmp_data = 0;
    CData/*7:0*/ top__DOT__my_ps2_to_ascii__DOT__tmp;
    top__DOT__my_ps2_to_ascii__DOT__tmp = 0;
    CData/*7:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    CData/*3:0*/ __Vtableidx2;
    __Vtableidx2 = 0;
    CData/*3:0*/ __Vtableidx3;
    __Vtableidx3 = 0;
    CData/*3:0*/ __Vtableidx4;
    __Vtableidx4 = 0;
    CData/*3:0*/ __Vtableidx5;
    __Vtableidx5 = 0;
    CData/*3:0*/ __Vtableidx6;
    __Vtableidx6 = 0;
    CData/*3:0*/ __Vtableidx7;
    __Vtableidx7 = 0;
    CData/*2:0*/ __Vdly__top__DOT__my_keyboard__DOT__ps2_clk_sync;
    __Vdly__top__DOT__my_keyboard__DOT__ps2_clk_sync = 0;
    CData/*3:0*/ __Vdly__top__DOT__my_keyboard__DOT__count;
    __Vdly__top__DOT__my_keyboard__DOT__count = 0;
    CData/*2:0*/ __Vdly__top__DOT__my_keyboard__DOT__w_ptr;
    __Vdly__top__DOT__my_keyboard__DOT__w_ptr = 0;
    CData/*2:0*/ __Vdly__top__DOT__my_keyboard__DOT__r_ptr;
    __Vdly__top__DOT__my_keyboard__DOT__r_ptr = 0;
    CData/*0:0*/ __Vdly__top__DOT__overflow;
    __Vdly__top__DOT__overflow = 0;
    CData/*0:0*/ __Vdly__top__DOT__ready;
    __Vdly__top__DOT__ready = 0;
    CData/*7:0*/ __Vdly__top__DOT__key_count;
    __Vdly__top__DOT__key_count = 0;
    CData/*2:0*/ __Vdlyvdim0__top__DOT__my_keyboard__DOT__fifo__v0;
    __Vdlyvdim0__top__DOT__my_keyboard__DOT__fifo__v0 = 0;
    CData/*7:0*/ __Vdlyvval__top__DOT__my_keyboard__DOT__fifo__v0;
    __Vdlyvval__top__DOT__my_keyboard__DOT__fifo__v0 = 0;
    CData/*0:0*/ __Vdlyvset__top__DOT__my_keyboard__DOT__fifo__v0;
    __Vdlyvset__top__DOT__my_keyboard__DOT__fifo__v0 = 0;
    // Body
    __Vdly__top__DOT__my_keyboard__DOT__ps2_clk_sync 
        = vlSelf->top__DOT__my_keyboard__DOT__ps2_clk_sync;
    __Vdly__top__DOT__overflow = vlSelf->top__DOT__overflow;
    __Vdly__top__DOT__my_keyboard__DOT__w_ptr = vlSelf->top__DOT__my_keyboard__DOT__w_ptr;
    __Vdly__top__DOT__my_keyboard__DOT__count = vlSelf->top__DOT__my_keyboard__DOT__count;
    __Vdly__top__DOT__key_count = vlSelf->top__DOT__key_count;
    __Vdly__top__DOT__ready = vlSelf->top__DOT__ready;
    __Vdly__top__DOT__my_keyboard__DOT__r_ptr = vlSelf->top__DOT__my_keyboard__DOT__r_ptr;
    __Vdlyvset__top__DOT__my_keyboard__DOT__fifo__v0 = 0U;
    __Vdly__top__DOT__my_keyboard__DOT__ps2_clk_sync 
        = ((6U & ((IData)(vlSelf->top__DOT__my_keyboard__DOT__ps2_clk_sync) 
                  << 1U)) | (IData)(vlSelf->ps2_clk));
    if (vlSelf->clrn) {
        __Vdly__top__DOT__my_keyboard__DOT__count = 0U;
        __Vdly__top__DOT__my_keyboard__DOT__w_ptr = 0U;
        __Vdly__top__DOT__my_keyboard__DOT__r_ptr = 0U;
        __Vdly__top__DOT__overflow = 0U;
        __Vdly__top__DOT__ready = 0U;
        __Vdly__top__DOT__key_count = 0U;
    } else {
        if (vlSelf->top__DOT__ready) {
            __Vdly__top__DOT__my_keyboard__DOT__r_ptr 
                = (7U & ((IData)(1U) + (IData)(vlSelf->top__DOT__my_keyboard__DOT__r_ptr)));
            if (((IData)(vlSelf->top__DOT__my_keyboard__DOT__w_ptr) 
                 == (7U & ((IData)(1U) + (IData)(vlSelf->top__DOT__my_keyboard__DOT__r_ptr))))) {
                __Vdly__top__DOT__ready = 0U;
            }
        }
        if ((IData)((4U == (6U & (IData)(vlSelf->top__DOT__my_keyboard__DOT__ps2_clk_sync))))) {
            if ((0xaU == (IData)(vlSelf->top__DOT__my_keyboard__DOT__count))) {
                if (VL_UNLIKELY((((~ (IData)(vlSelf->top__DOT__my_keyboard__DOT__buffer)) 
                                  & (IData)(vlSelf->ps2_data)) 
                                 & VL_REDXOR_32((0x1ffU 
                                                 & ((IData)(vlSelf->top__DOT__my_keyboard__DOT__buffer) 
                                                    >> 1U)))))) {
                    if ((0xf0U == (0xffU & ((IData)(vlSelf->top__DOT__my_keyboard__DOT__buffer) 
                                            >> 1U)))) {
                        __Vdly__top__DOT__key_count 
                            = (0xffU & ((IData)(1U) 
                                        + (IData)(vlSelf->top__DOT__key_count)));
                    }
                    VL_WRITEF("receive %x\n",8,(0xffU 
                                                & ((IData)(vlSelf->top__DOT__my_keyboard__DOT__buffer) 
                                                   >> 1U)));
                    __Vdlyvval__top__DOT__my_keyboard__DOT__fifo__v0 
                        = (0xffU & ((IData)(vlSelf->top__DOT__my_keyboard__DOT__buffer) 
                                    >> 1U));
                    __Vdlyvset__top__DOT__my_keyboard__DOT__fifo__v0 = 1U;
                    __Vdlyvdim0__top__DOT__my_keyboard__DOT__fifo__v0 
                        = vlSelf->top__DOT__my_keyboard__DOT__w_ptr;
                    __Vdly__top__DOT__ready = 1U;
                    __Vdly__top__DOT__my_keyboard__DOT__w_ptr 
                        = (7U & ((IData)(1U) + (IData)(vlSelf->top__DOT__my_keyboard__DOT__w_ptr)));
                    __Vdly__top__DOT__overflow = ((IData)(vlSelf->top__DOT__overflow) 
                                                  | ((IData)(vlSelf->top__DOT__my_keyboard__DOT__r_ptr) 
                                                     == 
                                                     (7U 
                                                      & ((IData)(1U) 
                                                         + (IData)(vlSelf->top__DOT__my_keyboard__DOT__w_ptr)))));
                }
                __Vdly__top__DOT__my_keyboard__DOT__count = 0U;
            } else {
                vlSelf->top__DOT__my_keyboard__DOT____Vlvbound_h1a91ade8__0 
                    = vlSelf->ps2_data;
                if ((9U >= (IData)(vlSelf->top__DOT__my_keyboard__DOT__count))) {
                    vlSelf->top__DOT__my_keyboard__DOT__buffer 
                        = (((~ ((IData)(1U) << (IData)(vlSelf->top__DOT__my_keyboard__DOT__count))) 
                            & (IData)(vlSelf->top__DOT__my_keyboard__DOT__buffer)) 
                           | (0x3ffU & ((IData)(vlSelf->top__DOT__my_keyboard__DOT____Vlvbound_h1a91ade8__0) 
                                        << (IData)(vlSelf->top__DOT__my_keyboard__DOT__count))));
                }
                __Vdly__top__DOT__my_keyboard__DOT__count 
                    = (0xfU & ((IData)(1U) + (IData)(vlSelf->top__DOT__my_keyboard__DOT__count)));
            }
        }
    }
    if ((1U != (IData)(vlSelf->top__DOT__state))) {
        vlSelf->seg3 = 0xffU;
        vlSelf->seg2 = 0xffU;
        vlSelf->seg1 = 0xffU;
        vlSelf->seg0 = 0xffU;
    } else if ((1U == (IData)(vlSelf->top__DOT__state))) {
        vlSelf->seg3 = vlSelf->top__DOT__tmp_seg3;
        vlSelf->seg2 = vlSelf->top__DOT__tmp_seg2;
        vlSelf->seg1 = vlSelf->top__DOT__tmp_seg1;
        vlSelf->seg0 = vlSelf->top__DOT__tmp_seg0;
    } else {
        vlSelf->seg3 = 0xffU;
        vlSelf->seg2 = 0xffU;
        vlSelf->seg1 = 0xffU;
        vlSelf->seg0 = 0xffU;
    }
    vlSelf->top__DOT__state = ((IData)(vlSelf->clrn)
                                ? 0U : (IData)(vlSelf->top__DOT__next_state));
    vlSelf->top__DOT__my_keyboard__DOT__count = __Vdly__top__DOT__my_keyboard__DOT__count;
    vlSelf->top__DOT__my_keyboard__DOT__w_ptr = __Vdly__top__DOT__my_keyboard__DOT__w_ptr;
    vlSelf->top__DOT__overflow = __Vdly__top__DOT__overflow;
    vlSelf->top__DOT__my_keyboard__DOT__ps2_clk_sync 
        = __Vdly__top__DOT__my_keyboard__DOT__ps2_clk_sync;
    vlSelf->top__DOT__key_count = __Vdly__top__DOT__key_count;
    vlSelf->top__DOT__ready = __Vdly__top__DOT__ready;
    vlSelf->top__DOT__my_keyboard__DOT__r_ptr = __Vdly__top__DOT__my_keyboard__DOT__r_ptr;
    if (__Vdlyvset__top__DOT__my_keyboard__DOT__fifo__v0) {
        vlSelf->top__DOT__my_keyboard__DOT__fifo[__Vdlyvdim0__top__DOT__my_keyboard__DOT__fifo__v0] 
            = __Vdlyvval__top__DOT__my_keyboard__DOT__fifo__v0;
    }
    __Vtableidx6 = (0xfU & (IData)(vlSelf->top__DOT__key_count));
    vlSelf->seg4 = Vtop__ConstPool__TABLE_h1f93ebb4_0
        [__Vtableidx6];
    __Vtableidx7 = (0xfU & ((IData)(vlSelf->top__DOT__key_count) 
                            >> 4U));
    vlSelf->seg5 = Vtop__ConstPool__TABLE_h1f93ebb4_0
        [__Vtableidx7];
    top__DOT__tmp_data = vlSelf->top__DOT__my_keyboard__DOT__fifo
        [vlSelf->top__DOT__my_keyboard__DOT__r_ptr];
    if (vlSelf->top__DOT__ready) {
        vlSelf->top__DOT__out_data = top__DOT__tmp_data;
        vlSelf->top__DOT__next_state = ((0U == (IData)(vlSelf->top__DOT__state))
                                         ? 1U : ((1U 
                                                  == (IData)(vlSelf->top__DOT__state))
                                                  ? 
                                                 ((0xf0U 
                                                   == (IData)(top__DOT__tmp_data))
                                                   ? 2U
                                                   : 1U)
                                                  : 
                                                 ((2U 
                                                   == (IData)(vlSelf->top__DOT__state))
                                                   ? 
                                                  ((0xf0U 
                                                    != (IData)(top__DOT__tmp_data))
                                                    ? 3U
                                                    : 2U)
                                                   : 
                                                  ((3U 
                                                    == (IData)(vlSelf->top__DOT__state))
                                                    ? 
                                                   ((0xf0U 
                                                     != (IData)(top__DOT__tmp_data))
                                                     ? 1U
                                                     : 3U)
                                                    : 0U))));
    } else {
        vlSelf->top__DOT__next_state = vlSelf->top__DOT__state;
    }
    if ((1U == (IData)(vlSelf->top__DOT__state))) {
        __Vtableidx2 = (0xfU & (IData)(vlSelf->top__DOT__out_data));
        __Vtableidx3 = (0xfU & ((IData)(vlSelf->top__DOT__out_data) 
                                >> 4U));
        __Vtableidx1 = vlSelf->top__DOT__out_data;
    } else {
        __Vtableidx2 = 0U;
        __Vtableidx3 = 0U;
        __Vtableidx1 = 0U;
    }
    vlSelf->top__DOT__tmp_seg0 = Vtop__ConstPool__TABLE_h1f93ebb4_0
        [__Vtableidx2];
    vlSelf->top__DOT__tmp_seg1 = Vtop__ConstPool__TABLE_h1f93ebb4_0
        [__Vtableidx3];
    top__DOT__my_ps2_to_ascii__DOT__tmp = Vtop__ConstPool__TABLE_h181586bb_0
        [__Vtableidx1];
    __Vtableidx4 = (0xfU & (IData)(top__DOT__my_ps2_to_ascii__DOT__tmp));
    vlSelf->top__DOT__tmp_seg2 = Vtop__ConstPool__TABLE_h1f93ebb4_0
        [__Vtableidx4];
    __Vtableidx5 = (0xfU & ((IData)(top__DOT__my_ps2_to_ascii__DOT__tmp) 
                            >> 4U));
    vlSelf->top__DOT__tmp_seg3 = Vtop__ConstPool__TABLE_h1f93ebb4_0
        [__Vtableidx5];
}

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    // Body
    if (vlSelf->__VnbaTriggered.at(0U)) {
        Vtop___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vtop___024root___eval_triggers__act(Vtop___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf);
#endif  // VL_DEBUG

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    // Init
    VlTriggerVec<1> __VpreTriggered;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        __VnbaContinue = 0U;
        vlSelf->__VnbaTriggered.clear();
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            vlSelf->__VactContinue = 0U;
            Vtop___024root___eval_triggers__act(vlSelf);
            if (vlSelf->__VactTriggered.any()) {
                vlSelf->__VactContinue = 1U;
                if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                    Vtop___024root___dump_triggers__act(vlSelf);
#endif
                    VL_FATAL_MT("/home/curry/code/ysyx_curry/digtal_test/test7/vsrc/top.v", 1, "", "Active region did not converge.");
                }
                vlSelf->__VactIterCount = ((IData)(1U) 
                                           + vlSelf->__VactIterCount);
                __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
                vlSelf->__VnbaTriggered.set(vlSelf->__VactTriggered);
                Vtop___024root___eval_act(vlSelf);
            }
        }
        if (vlSelf->__VnbaTriggered.any()) {
            __VnbaContinue = 1U;
            if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__nba(vlSelf);
#endif
                VL_FATAL_MT("/home/curry/code/ysyx_curry/digtal_test/test7/vsrc/top.v", 1, "", "NBA region did not converge.");
            }
            __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
            Vtop___024root___eval_nba(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->clrn & 0xfeU))) {
        Verilated::overWidthError("clrn");}
    if (VL_UNLIKELY((vlSelf->ps2_clk & 0xfeU))) {
        Verilated::overWidthError("ps2_clk");}
    if (VL_UNLIKELY((vlSelf->ps2_data & 0xfeU))) {
        Verilated::overWidthError("ps2_data");}
}
#endif  // VL_DEBUG
