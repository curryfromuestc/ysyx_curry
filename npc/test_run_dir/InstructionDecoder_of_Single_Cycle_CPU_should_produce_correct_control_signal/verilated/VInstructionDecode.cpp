// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VInstructionDecode.h"
#include "VInstructionDecode__Syms.h"

//============================================================
// Constructors

VInstructionDecode::VInstructionDecode(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new VInstructionDecode__Syms(contextp(), _vcname__, this)}
    , clock{vlSymsp->TOP.clock}
    , reset{vlSymsp->TOP.reset}
    , io_regs_reg1_read_address{vlSymsp->TOP.io_regs_reg1_read_address}
    , io_regs_reg2_read_address{vlSymsp->TOP.io_regs_reg2_read_address}
    , io_ex_aluop1_source{vlSymsp->TOP.io_ex_aluop1_source}
    , io_ex_aluop2_source{vlSymsp->TOP.io_ex_aluop2_source}
    , io_memory_read_enable{vlSymsp->TOP.io_memory_read_enable}
    , io_memory_write_enable{vlSymsp->TOP.io_memory_write_enable}
    , io_wb_reg_write_source{vlSymsp->TOP.io_wb_reg_write_source}
    , io_reg_write_enable{vlSymsp->TOP.io_reg_write_enable}
    , io_reg_write_address{vlSymsp->TOP.io_reg_write_address}
    , io_instruction{vlSymsp->TOP.io_instruction}
    , io_ex_immediate{vlSymsp->TOP.io_ex_immediate}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

VInstructionDecode::VInstructionDecode(const char* _vcname__)
    : VInstructionDecode(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

VInstructionDecode::~VInstructionDecode() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void VInstructionDecode___024root___eval_debug_assertions(VInstructionDecode___024root* vlSelf);
#endif  // VL_DEBUG
void VInstructionDecode___024root___eval_static(VInstructionDecode___024root* vlSelf);
void VInstructionDecode___024root___eval_initial(VInstructionDecode___024root* vlSelf);
void VInstructionDecode___024root___eval_settle(VInstructionDecode___024root* vlSelf);
void VInstructionDecode___024root___eval(VInstructionDecode___024root* vlSelf);

void VInstructionDecode::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VInstructionDecode::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    VInstructionDecode___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        VInstructionDecode___024root___eval_static(&(vlSymsp->TOP));
        VInstructionDecode___024root___eval_initial(&(vlSymsp->TOP));
        VInstructionDecode___024root___eval_settle(&(vlSymsp->TOP));
    }
    // MTask 0 start
    VL_DEBUG_IF(VL_DBG_MSGF("MTask0 starting\n"););
    Verilated::mtaskId(0);
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    VInstructionDecode___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool VInstructionDecode::eventsPending() { return false; }

uint64_t VInstructionDecode::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* VInstructionDecode::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void VInstructionDecode___024root___eval_final(VInstructionDecode___024root* vlSelf);

VL_ATTR_COLD void VInstructionDecode::final() {
    VInstructionDecode___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* VInstructionDecode::hierName() const { return vlSymsp->name(); }
const char* VInstructionDecode::modelName() const { return "VInstructionDecode"; }
unsigned VInstructionDecode::threads() const { return 1; }
