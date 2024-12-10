// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


VL_ATTR_COLD void Vtop___024root__trace_init_sub__TOP__0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+34,"clk", false,-1);
    tracep->declBit(c+35,"clrn", false,-1);
    tracep->declBit(c+36,"ps2_clk", false,-1);
    tracep->declBit(c+37,"ps2_data", false,-1);
    tracep->declBus(c+38,"seg0", false,-1, 7,0);
    tracep->declBus(c+39,"seg1", false,-1, 7,0);
    tracep->declBus(c+40,"seg2", false,-1, 7,0);
    tracep->declBus(c+41,"seg3", false,-1, 7,0);
    tracep->declBus(c+42,"seg4", false,-1, 7,0);
    tracep->declBus(c+43,"seg5", false,-1, 7,0);
    tracep->declBus(c+44,"seg6", false,-1, 7,0);
    tracep->declBus(c+45,"seg7", false,-1, 7,0);
    tracep->pushNamePrefix("top ");
    tracep->declBit(c+34,"clk", false,-1);
    tracep->declBit(c+35,"clrn", false,-1);
    tracep->declBit(c+36,"ps2_clk", false,-1);
    tracep->declBit(c+37,"ps2_data", false,-1);
    tracep->declBus(c+38,"seg0", false,-1, 7,0);
    tracep->declBus(c+39,"seg1", false,-1, 7,0);
    tracep->declBus(c+40,"seg2", false,-1, 7,0);
    tracep->declBus(c+41,"seg3", false,-1, 7,0);
    tracep->declBus(c+42,"seg4", false,-1, 7,0);
    tracep->declBus(c+43,"seg5", false,-1, 7,0);
    tracep->declBus(c+44,"seg6", false,-1, 7,0);
    tracep->declBus(c+45,"seg7", false,-1, 7,0);
    tracep->declBit(c+46,"nextdata_n", false,-1);
    tracep->declBit(c+1,"overflow", false,-1);
    tracep->declBus(c+2,"data", false,-1, 7,0);
    tracep->declBus(c+3,"tmp_data", false,-1, 7,0);
    tracep->declBus(c+4,"out_data", false,-1, 7,0);
    tracep->declBus(c+5,"key_count", false,-1, 7,0);
    tracep->declBus(c+6,"ascii", false,-1, 7,0);
    tracep->declBit(c+7,"ready", false,-1);
    tracep->declBus(c+8,"tmp_seg0", false,-1, 7,0);
    tracep->declBus(c+9,"tmp_seg1", false,-1, 7,0);
    tracep->declBus(c+10,"tmp_seg2", false,-1, 7,0);
    tracep->declBus(c+11,"tmp_seg3", false,-1, 7,0);
    tracep->declBus(c+47,"a", false,-1, 3,0);
    tracep->declBus(c+48,"b", false,-1, 3,0);
    tracep->declBus(c+49,"c", false,-1, 3,0);
    tracep->declBus(c+50,"d", false,-1, 3,0);
    tracep->declBus(c+12,"state", false,-1, 3,0);
    tracep->declBus(c+13,"next_state", false,-1, 3,0);
    tracep->pushNamePrefix("my_keyboard ");
    tracep->declBit(c+34,"clk", false,-1);
    tracep->declBit(c+35,"clrn", false,-1);
    tracep->declBit(c+36,"ps2_clk", false,-1);
    tracep->declBit(c+37,"ps2_data", false,-1);
    tracep->declBit(c+46,"nextdata_n", false,-1);
    tracep->declBus(c+3,"data", false,-1, 7,0);
    tracep->declBit(c+7,"ready", false,-1);
    tracep->declBit(c+1,"overflow", false,-1);
    tracep->declBus(c+5,"key_count", false,-1, 7,0);
    tracep->declBus(c+14,"buffer", false,-1, 9,0);
    for (int i = 0; i < 8; ++i) {
        tracep->declBus(c+15+i*1,"fifo", true,(i+0), 7,0);
    }
    tracep->declBus(c+23,"w_ptr", false,-1, 2,0);
    tracep->declBus(c+24,"r_ptr", false,-1, 2,0);
    tracep->declBus(c+25,"count", false,-1, 3,0);
    tracep->declBus(c+26,"ps2_clk_sync", false,-1, 2,0);
    tracep->declBit(c+27,"sampling", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("my_ps2_to_ascii ");
    tracep->declBus(c+2,"x", false,-1, 7,0);
    tracep->declBus(c+6,"y", false,-1, 7,0);
    tracep->declBus(c+6,"tmp", false,-1, 7,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("my_seg1 ");
    tracep->declBus(c+28,"b", false,-1, 3,0);
    tracep->declBus(c+8,"h", false,-1, 7,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("my_seg2 ");
    tracep->declBus(c+29,"b", false,-1, 3,0);
    tracep->declBus(c+9,"h", false,-1, 7,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("my_seg3 ");
    tracep->declBus(c+30,"b", false,-1, 3,0);
    tracep->declBus(c+10,"h", false,-1, 7,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("my_seg4 ");
    tracep->declBus(c+31,"b", false,-1, 3,0);
    tracep->declBus(c+11,"h", false,-1, 7,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("my_seg5 ");
    tracep->declBus(c+32,"b", false,-1, 3,0);
    tracep->declBus(c+42,"h", false,-1, 7,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("my_seg6 ");
    tracep->declBus(c+33,"b", false,-1, 3,0);
    tracep->declBus(c+43,"h", false,-1, 7,0);
    tracep->popNamePrefix(2);
}

VL_ATTR_COLD void Vtop___024root__trace_init_top(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_top\n"); );
    // Body
    Vtop___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vtop___024root__trace_register(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_register\n"); );
    // Body
    tracep->addFullCb(&Vtop___024root__trace_full_top_0, vlSelf);
    tracep->addChgCb(&Vtop___024root__trace_chg_top_0, vlSelf);
    tracep->addCleanupCb(&Vtop___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtop___024root__trace_full_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_top_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vtop___024root__trace_full_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtop___024root__trace_full_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullBit(oldp+1,(vlSelf->top__DOT__overflow));
    bufp->fullCData(oldp+2,(((1U == (IData)(vlSelf->top__DOT__state))
                              ? (IData)(vlSelf->top__DOT__out_data)
                              : 0U)),8);
    bufp->fullCData(oldp+3,(vlSelf->top__DOT__tmp_data),8);
    bufp->fullCData(oldp+4,(vlSelf->top__DOT__out_data),8);
    bufp->fullCData(oldp+5,(vlSelf->top__DOT__key_count),8);
    bufp->fullCData(oldp+6,(vlSelf->top__DOT__my_ps2_to_ascii__DOT__tmp),8);
    bufp->fullBit(oldp+7,(vlSelf->top__DOT__ready));
    bufp->fullCData(oldp+8,(vlSelf->top__DOT__tmp_seg0),8);
    bufp->fullCData(oldp+9,(vlSelf->top__DOT__tmp_seg1),8);
    bufp->fullCData(oldp+10,(vlSelf->top__DOT__tmp_seg2),8);
    bufp->fullCData(oldp+11,(vlSelf->top__DOT__tmp_seg3),8);
    bufp->fullCData(oldp+12,(vlSelf->top__DOT__state),4);
    bufp->fullCData(oldp+13,(vlSelf->top__DOT__next_state),4);
    bufp->fullSData(oldp+14,(vlSelf->top__DOT__my_keyboard__DOT__buffer),10);
    bufp->fullCData(oldp+15,(vlSelf->top__DOT__my_keyboard__DOT__fifo[0]),8);
    bufp->fullCData(oldp+16,(vlSelf->top__DOT__my_keyboard__DOT__fifo[1]),8);
    bufp->fullCData(oldp+17,(vlSelf->top__DOT__my_keyboard__DOT__fifo[2]),8);
    bufp->fullCData(oldp+18,(vlSelf->top__DOT__my_keyboard__DOT__fifo[3]),8);
    bufp->fullCData(oldp+19,(vlSelf->top__DOT__my_keyboard__DOT__fifo[4]),8);
    bufp->fullCData(oldp+20,(vlSelf->top__DOT__my_keyboard__DOT__fifo[5]),8);
    bufp->fullCData(oldp+21,(vlSelf->top__DOT__my_keyboard__DOT__fifo[6]),8);
    bufp->fullCData(oldp+22,(vlSelf->top__DOT__my_keyboard__DOT__fifo[7]),8);
    bufp->fullCData(oldp+23,(vlSelf->top__DOT__my_keyboard__DOT__w_ptr),3);
    bufp->fullCData(oldp+24,(vlSelf->top__DOT__my_keyboard__DOT__r_ptr),3);
    bufp->fullCData(oldp+25,(vlSelf->top__DOT__my_keyboard__DOT__count),4);
    bufp->fullCData(oldp+26,(vlSelf->top__DOT__my_keyboard__DOT__ps2_clk_sync),3);
    bufp->fullBit(oldp+27,((IData)((4U == (6U & (IData)(vlSelf->top__DOT__my_keyboard__DOT__ps2_clk_sync))))));
    bufp->fullCData(oldp+28,(((1U == (IData)(vlSelf->top__DOT__state))
                               ? (0xfU & (IData)(vlSelf->top__DOT__out_data))
                               : 0U)),4);
    bufp->fullCData(oldp+29,(((1U == (IData)(vlSelf->top__DOT__state))
                               ? (0xfU & ((IData)(vlSelf->top__DOT__out_data) 
                                          >> 4U)) : 0U)),4);
    bufp->fullCData(oldp+30,((0xfU & (IData)(vlSelf->top__DOT__my_ps2_to_ascii__DOT__tmp))),4);
    bufp->fullCData(oldp+31,((0xfU & ((IData)(vlSelf->top__DOT__my_ps2_to_ascii__DOT__tmp) 
                                      >> 4U))),4);
    bufp->fullCData(oldp+32,((0xfU & (IData)(vlSelf->top__DOT__key_count))),4);
    bufp->fullCData(oldp+33,((0xfU & ((IData)(vlSelf->top__DOT__key_count) 
                                      >> 4U))),4);
    bufp->fullBit(oldp+34,(vlSelf->clk));
    bufp->fullBit(oldp+35,(vlSelf->clrn));
    bufp->fullBit(oldp+36,(vlSelf->ps2_clk));
    bufp->fullBit(oldp+37,(vlSelf->ps2_data));
    bufp->fullCData(oldp+38,(vlSelf->seg0),8);
    bufp->fullCData(oldp+39,(vlSelf->seg1),8);
    bufp->fullCData(oldp+40,(vlSelf->seg2),8);
    bufp->fullCData(oldp+41,(vlSelf->seg3),8);
    bufp->fullCData(oldp+42,(vlSelf->seg4),8);
    bufp->fullCData(oldp+43,(vlSelf->seg5),8);
    bufp->fullCData(oldp+44,(vlSelf->seg6),8);
    bufp->fullCData(oldp+45,(vlSelf->seg7),8);
    bufp->fullBit(oldp+46,(vlSelf->top__DOT__nextdata_n));
    bufp->fullCData(oldp+47,(0U),4);
    bufp->fullCData(oldp+48,(1U),4);
    bufp->fullCData(oldp+49,(2U),4);
    bufp->fullCData(oldp+50,(4U),4);
}
