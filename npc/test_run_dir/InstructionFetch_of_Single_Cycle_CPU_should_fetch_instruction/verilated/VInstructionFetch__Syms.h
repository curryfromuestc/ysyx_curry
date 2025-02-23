// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VINSTRUCTIONFETCH__SYMS_H_
#define VERILATED_VINSTRUCTIONFETCH__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "VInstructionFetch.h"

// INCLUDE MODULE CLASSES
#include "VInstructionFetch___024root.h"

// SYMS CLASS (contains all model state)
class VInstructionFetch__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    VInstructionFetch* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    VInstructionFetch___024root    TOP;

    // CONSTRUCTORS
    VInstructionFetch__Syms(VerilatedContext* contextp, const char* namep, VInstructionFetch* modelp);
    ~VInstructionFetch__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
