// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VINSTRUCTIONDECODE__SYMS_H_
#define VERILATED_VINSTRUCTIONDECODE__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "VInstructionDecode.h"

// INCLUDE MODULE CLASSES
#include "VInstructionDecode___024root.h"

// SYMS CLASS (contains all model state)
class VInstructionDecode__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    VInstructionDecode* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    VInstructionDecode___024root   TOP;

    // CONSTRUCTORS
    VInstructionDecode__Syms(VerilatedContext* contextp, const char* namep, VInstructionDecode* modelp);
    ~VInstructionDecode__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
