// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary model header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef VERILATED_VMEMORYCONTROL_H_
#define VERILATED_VMEMORYCONTROL_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"

class VMemoryControl__Syms;
class VMemoryControl___024root;

// This class is the main interface to the Verilated model
class VMemoryControl VL_NOT_FINAL : public VerilatedModel {
  private:
    // Symbol table holding complete model state (owned by this class)
    VMemoryControl__Syms* const vlSymsp;

  public:

    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(&clock,0,0);
    VL_IN8(&reset,0,0);
    VL_IN8(&io_memory_read_enable,0,0);
    VL_IN8(&io_memory_write_enable,0,0);
    VL_IN8(&io_funct3,2,0);
    VL_OUT8(&io_memory_bundle_write_enable,0,0);
    VL_OUT8(&io_memory_bundle_write_strobe_0,0,0);
    VL_OUT8(&io_memory_bundle_write_strobe_1,0,0);
    VL_OUT8(&io_memory_bundle_write_strobe_2,0,0);
    VL_OUT8(&io_memory_bundle_write_strobe_3,0,0);
    VL_IN(&io_alu_result,31,0);
    VL_IN(&io_reg2_data,31,0);
    VL_OUT(&io_wb_memory_read_data,31,0);
    VL_OUT(&io_memory_bundle_address,31,0);
    VL_IN(&io_memory_bundle_read_data,31,0);
    VL_OUT(&io_memory_bundle_write_data,31,0);

    // CELLS
    // Public to allow access to /* verilator public */ items.
    // Otherwise the application code can consider these internals.

    // Root instance pointer to allow access to model internals,
    // including inlined /* verilator public_flat_* */ items.
    VMemoryControl___024root* const rootp;

    // CONSTRUCTORS
    /// Construct the model; called by application code
    /// If contextp is null, then the model will use the default global context
    /// If name is "", then makes a wrapper with a
    /// single model invisible with respect to DPI scope names.
    explicit VMemoryControl(VerilatedContext* contextp, const char* name = "TOP");
    explicit VMemoryControl(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    virtual ~VMemoryControl();
  private:
    VL_UNCOPYABLE(VMemoryControl);  ///< Copying not allowed

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
