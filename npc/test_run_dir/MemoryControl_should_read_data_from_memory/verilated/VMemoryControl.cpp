// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VMemoryControl.h"
#include "VMemoryControl__Syms.h"

//============================================================
// Constructors

VMemoryControl::VMemoryControl(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new VMemoryControl__Syms(contextp(), _vcname__, this)}
    , clock{vlSymsp->TOP.clock}
    , reset{vlSymsp->TOP.reset}
    , io_memory_read_enable{vlSymsp->TOP.io_memory_read_enable}
    , io_memory_write_enable{vlSymsp->TOP.io_memory_write_enable}
    , io_funct3{vlSymsp->TOP.io_funct3}
    , io_memory_bundle_write_enable{vlSymsp->TOP.io_memory_bundle_write_enable}
    , io_memory_bundle_write_strobe_0{vlSymsp->TOP.io_memory_bundle_write_strobe_0}
    , io_memory_bundle_write_strobe_1{vlSymsp->TOP.io_memory_bundle_write_strobe_1}
    , io_memory_bundle_write_strobe_2{vlSymsp->TOP.io_memory_bundle_write_strobe_2}
    , io_memory_bundle_write_strobe_3{vlSymsp->TOP.io_memory_bundle_write_strobe_3}
    , io_alu_result{vlSymsp->TOP.io_alu_result}
    , io_reg2_data{vlSymsp->TOP.io_reg2_data}
    , io_wb_memory_read_data{vlSymsp->TOP.io_wb_memory_read_data}
    , io_memory_bundle_address{vlSymsp->TOP.io_memory_bundle_address}
    , io_memory_bundle_read_data{vlSymsp->TOP.io_memory_bundle_read_data}
    , io_memory_bundle_write_data{vlSymsp->TOP.io_memory_bundle_write_data}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

VMemoryControl::VMemoryControl(const char* _vcname__)
    : VMemoryControl(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

VMemoryControl::~VMemoryControl() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void VMemoryControl___024root___eval_debug_assertions(VMemoryControl___024root* vlSelf);
#endif  // VL_DEBUG
void VMemoryControl___024root___eval_static(VMemoryControl___024root* vlSelf);
void VMemoryControl___024root___eval_initial(VMemoryControl___024root* vlSelf);
void VMemoryControl___024root___eval_settle(VMemoryControl___024root* vlSelf);
void VMemoryControl___024root___eval(VMemoryControl___024root* vlSelf);

void VMemoryControl::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VMemoryControl::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    VMemoryControl___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        VMemoryControl___024root___eval_static(&(vlSymsp->TOP));
        VMemoryControl___024root___eval_initial(&(vlSymsp->TOP));
        VMemoryControl___024root___eval_settle(&(vlSymsp->TOP));
    }
    // MTask 0 start
    VL_DEBUG_IF(VL_DBG_MSGF("MTask0 starting\n"););
    Verilated::mtaskId(0);
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    VMemoryControl___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool VMemoryControl::eventsPending() { return false; }

uint64_t VMemoryControl::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* VMemoryControl::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void VMemoryControl___024root___eval_final(VMemoryControl___024root* vlSelf);

VL_ATTR_COLD void VMemoryControl::final() {
    VMemoryControl___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* VMemoryControl::hierName() const { return vlSymsp->name(); }
const char* VMemoryControl::modelName() const { return "VMemoryControl"; }
unsigned VMemoryControl::threads() const { return 1; }
