// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary model header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef VERILATED_VINSTRUCTIONDECODE_H_
#define VERILATED_VINSTRUCTIONDECODE_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"

class VInstructionDecode__Syms;
class VInstructionDecode___024root;

// This class is the main interface to the Verilated model
class VInstructionDecode VL_NOT_FINAL : public VerilatedModel {
  private:
    // Symbol table holding complete model state (owned by this class)
    VInstructionDecode__Syms* const vlSymsp;

  public:

    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(&clock,0,0);
    VL_IN8(&reset,0,0);
    VL_OUT8(&io_regs_reg1_read_address,4,0);
    VL_OUT8(&io_regs_reg2_read_address,4,0);
    VL_OUT8(&io_ex_aluop1_source,0,0);
    VL_OUT8(&io_ex_aluop2_source,0,0);
    VL_OUT8(&io_memory_read_enable,0,0);
    VL_OUT8(&io_memory_write_enable,0,0);
    VL_OUT8(&io_wb_reg_write_source,1,0);
    VL_OUT8(&io_reg_write_enable,0,0);
    VL_OUT8(&io_reg_write_address,4,0);
    VL_IN(&io_instruction,31,0);
    VL_OUT(&io_ex_immediate,31,0);

    // CELLS
    // Public to allow access to /* verilator public */ items.
    // Otherwise the application code can consider these internals.

    // Root instance pointer to allow access to model internals,
    // including inlined /* verilator public_flat_* */ items.
    VInstructionDecode___024root* const rootp;

    // CONSTRUCTORS
    /// Construct the model; called by application code
    /// If contextp is null, then the model will use the default global context
    /// If name is "", then makes a wrapper with a
    /// single model invisible with respect to DPI scope names.
    explicit VInstructionDecode(VerilatedContext* contextp, const char* name = "TOP");
    explicit VInstructionDecode(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    virtual ~VInstructionDecode();
  private:
    VL_UNCOPYABLE(VInstructionDecode);  ///< Copying not allowed

  public:
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    /// Are there scheduled events to handle?
    bool eventsPending();
    /// Returns time at next time slot. Aborts if !eventsPending()
    uint64_t nextTimeSlot();
    /// Retrieve name of this model instance (as passed to constructor).
    const char* name() const;

    // Abstract methods from VerilatedModel
    const char* hierName() const override final;
    const char* modelName() const override final;
    unsigned threads() const override final;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
