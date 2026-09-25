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
//
// TODO: Port the field barrier (used by LXR) to aarch64. Only the assembler part is missing.
// The runtime, C1 (LIR) and C2 (IdealKit) parts are shared in share/barriers/mmtkFieldBarrier.cpp.
// Use cpu/x86/mmtkFieldBarrierSetAssembler_x86.cpp as the reference, and remove the constructor
// below once done. We need:
// - object_reference_write_pre: the pre-write barrier used by the interpreter. Check the field's
//   unlog bit (one bit per slot: `slot >> (UseCompressedOops ? 5 : 6)` selects the byte in
//   side_metadata_base_address(), `(slot >> (UseCompressedOops ? 2 : 3)) & 7` the bit), and call
//   object_reference_write_slow_call(src, slot, val) if it is set. This runs before
//   BarrierSetAssembler::store_at, so `val` is still uncompressed here. If a post barrier ever
//   needs `val`, copy it before store_at (see G1BarrierSetAssembler::oop_store_at), because
//   store_at compresses `val` in place.
// - load_at: the weak reference load barrier. Call load_reference_call on non-null oops loaded
//   with ON_WEAK_OOP_REF/ON_PHANTOM_OOP_REF while CONCURRENT_MARKING_ACTIVE is set.
//   MMTkSATBBarrierSetAssembler::load_at for aarch64 already does the same thing.
// - arraycopy_prologue: call object_reference_array_copy_pre_call for oop arrays (note the aarch64
//   signature, as in MMTkSATBBarrierSetAssembler).
// - generate_c1_pre_write_barrier_stub: the C1 slow-path stub. When the field needs patching,
//   resolve the address into stub->scratch and call the "with_patch_fix" runtime stub (already
//   generated for aarch64 in MMTkBarrierSetAssembler).
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
