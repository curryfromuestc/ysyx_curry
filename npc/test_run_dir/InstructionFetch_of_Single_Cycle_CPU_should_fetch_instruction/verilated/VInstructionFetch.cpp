// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VInstructionFetch.h"
#include "VInstructionFetch__Syms.h"

//============================================================
// Constructors

VInstructionFetch::VInstructionFetch(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new VInstructionFetch__Syms(contextp(), _vcname__, this)}
    , clock{vlSymsp->TOP.clock}
    , reset{vlSymsp->TOP.reset}
    , io_jump_flag_id{vlSymsp->TOP.io_jump_flag_id}
    , io_instruction_valid{vlSymsp->TOP.io_instruction_valid}
    , io_jump_address_id{vlSymsp->TOP.io_jump_address_id}
    , io_instruction_read_data{vlSymsp->TOP.io_instruction_read_data}
    , io_instruction_address{vlSymsp->TOP.io_instruction_address}
    , io_instruction{vlSymsp->TOP.io_instruction}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

VInstructionFetch::VInstructionFetch(const char* _vcname__)
    : VInstructionFetch(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

VInstructionFetch::~VInstructionFetch() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void VInstructionFetch___024root___eval_debug_assertions(VInstructionFetch___024root* vlSelf);
#endif  // VL_DEBUG
void VInstructionFetch___024root___eval_static(VInstructionFetch___024root* vlSelf);
void VInstructionFetch___024root___eval_initial(VInstructionFetch___024root* vlSelf);
void VInstructionFetch___024root___eval_settle(VInstructionFetch___024root* vlSelf);
void VInstructionFetch___024root___eval(VInstructionFetch___024root* vlSelf);

void VInstructionFetch::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VInstructionFetch::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    VInstructionFetch___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        VInstructionFetch___024root___eval_static(&(vlSymsp->TOP));
        VInstructionFetch___024root___eval_initial(&(vlSymsp->TOP));
        VInstructionFetch___024root___eval_settle(&(vlSymsp->TOP));
    }
    // MTask 0 start
    VL_DEBUG_IF(VL_DBG_MSGF("MTask0 starting\n"););
    Verilated::mtaskId(0);
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    VInstructionFetch___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool VInstructionFetch::eventsPending() { return false; }

uint64_t VInstructionFetch::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* VInstructionFetch::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void VInstructionFetch___024root___eval_final(VInstructionFetch___024root* vlSelf);

VL_ATTR_COLD void VInstructionFetch::final() {
    VInstructionFetch___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* VInstructionFetch::hierName() const { return vlSymsp->name(); }
const char* VInstructionFetch::modelName() const { return "VInstructionFetch"; }
unsigned VInstructionFetch::threads() const { return 1; }
