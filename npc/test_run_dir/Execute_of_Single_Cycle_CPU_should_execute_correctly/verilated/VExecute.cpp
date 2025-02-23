// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VExecute.h"
#include "VExecute__Syms.h"

//============================================================
// Constructors

VExecute::VExecute(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new VExecute__Syms(contextp(), _vcname__, this)}
    , clock{vlSymsp->TOP.clock}
    , reset{vlSymsp->TOP.reset}
    , io_aluop1_source{vlSymsp->TOP.io_aluop1_source}
    , io_aluop2_source{vlSymsp->TOP.io_aluop2_source}
    , io_if_jump_flag{vlSymsp->TOP.io_if_jump_flag}
    , io_instruction{vlSymsp->TOP.io_instruction}
    , io_instruction_address{vlSymsp->TOP.io_instruction_address}
    , io_reg1_data{vlSymsp->TOP.io_reg1_data}
    , io_reg2_data{vlSymsp->TOP.io_reg2_data}
    , io_immediate{vlSymsp->TOP.io_immediate}
    , io_mem_alu_result{vlSymsp->TOP.io_mem_alu_result}
    , io_if_jump_address{vlSymsp->TOP.io_if_jump_address}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

VExecute::VExecute(const char* _vcname__)
    : VExecute(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

VExecute::~VExecute() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void VExecute___024root___eval_debug_assertions(VExecute___024root* vlSelf);
#endif  // VL_DEBUG
void VExecute___024root___eval_static(VExecute___024root* vlSelf);
void VExecute___024root___eval_initial(VExecute___024root* vlSelf);
void VExecute___024root___eval_settle(VExecute___024root* vlSelf);
void VExecute___024root___eval(VExecute___024root* vlSelf);

void VExecute::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VExecute::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    VExecute___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        VExecute___024root___eval_static(&(vlSymsp->TOP));
        VExecute___024root___eval_initial(&(vlSymsp->TOP));
        VExecute___024root___eval_settle(&(vlSymsp->TOP));
    }
    // MTask 0 start
    VL_DEBUG_IF(VL_DBG_MSGF("MTask0 starting\n"););
    Verilated::mtaskId(0);
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    VExecute___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool VExecute::eventsPending() { return false; }

uint64_t VExecute::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* VExecute::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void VExecute___024root___eval_final(VExecute___024root* vlSelf);

VL_ATTR_COLD void VExecute::final() {
    VExecute___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* VExecute::hierName() const { return vlSymsp->name(); }
const char* VExecute::modelName() const { return "VExecute"; }
unsigned VExecute::threads() const { return 1; }
