//===-- MYRISCVXSubtarget.h - Define Subtarget for the MYRISCVX ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===-----------------------------------------------------------------------===//
//
// This file declares the MYRISCVX specific subclass of TargetSubtargetInfo.
//
//===-----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MYRISCVX_MYRISCVXSUBTARGET_H
#define LLVM_LIB_TARGET_MYRISCVX_MYRISCVXSUBTARGET_H

#include "MYRISCVXFrameLowering.h"
#include "MYRISCVXISelLowering.h"
#include "MYRISCVXInstrInfo.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/MC/MCInstrItineraries.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include <string>

namespace llvm {
  class StringRef;
  class MYRISCXVTargetMachine;
  class MYRISCVXSubtarget : public MYRISCVXGenSubtargetInfo {
    virtual void anchor();
public:
protected:
  bool IsRV64 = false;
  MVT RegType = MVT::i32;
}
}

#endif // LLVM_LIB_TARGET_MYRISCVX_MYRISCVXSUBTARGET_H