// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VMEMORYCONTROL__SYMS_H_
#define VERILATED_VMEMORYCONTROL__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "VMemoryControl.h"

// INCLUDE MODULE CLASSES
#include "VMemoryControl___024root.h"

// SYMS CLASS (contains all model state)
class VMemoryControl__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    VMemoryControl* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    VMemoryControl___024root       TOP;

    // CONSTRUCTORS
    VMemoryControl__Syms(VerilatedContext* contextp, const char* namep, VMemoryControl* modelp);
    ~VMemoryControl__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
