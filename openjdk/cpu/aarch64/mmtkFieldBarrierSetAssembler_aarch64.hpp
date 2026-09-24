#ifndef MMTK_OPENJDK_MMTK_FIELD_BARRIER_SET_ASSEMBLER_AARCH64_HPP
#define MMTK_OPENJDK_MMTK_FIELD_BARRIER_SET_ASSEMBLER_AARCH64_HPP

#include "utilities/debug.hpp"
#include "utilities/macros.hpp"
#include CPU_HEADER(mmtkBarrierSetAssembler)

struct MMTkC1FieldBarrierStub;

//////////////////// Assembler ////////////////////

// The field barrier is not implemented for aarch64 yet. This empty implementation only lets the
// shared part of the barrier compile. The assembler is only created for the selected barrier,
// so we fail fast here instead of running without the barrier in generated code.
class MMTkFieldBarrierSetAssembler: public MMTkBarrierSetAssembler {
public:
  MMTkFieldBarrierSetAssembler() {
    fatal("FieldBarrier is not implemented for aarch64");
  }
  virtual void generate_c1_pre_write_barrier_stub(LIR_Assembler* ce, MMTkC1FieldBarrierStub* stub) const {
    Unimplemented();
  }
};

#endif // MMTK_OPENJDK_MMTK_FIELD_BARRIER_SET_ASSEMBLER_AARCH64_HPP
