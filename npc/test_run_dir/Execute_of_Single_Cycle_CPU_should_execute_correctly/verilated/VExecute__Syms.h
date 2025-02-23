// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VEXECUTE__SYMS_H_
#define VERILATED_VEXECUTE__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "VExecute.h"

// INCLUDE MODULE CLASSES
#include "VExecute___024root.h"

// SYMS CLASS (contains all model state)
class VExecute__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    VExecute* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    VExecute___024root             TOP;

    // CONSTRUCTORS
    VExecute__Syms(VerilatedContext* contextp, const char* namep, VExecute* modelp);
    ~VExecute__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
