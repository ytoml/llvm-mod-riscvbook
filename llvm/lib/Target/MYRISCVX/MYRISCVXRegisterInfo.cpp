//===-- MYRISCVXRegisterInfo.cpp - MYRISCVX Register Information -== ------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the MYRISCVX implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "MYRISCVX.h"
#include "MYRISCVXRegisterInfo.h"
#include "MYRISCVXSubtarget.h"
#include "MYRISCVXMachineFunction.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "MYRISCVX-reg-info"

#define GET_REGINFO_TARGET_DESC
#define GET_REGINFO_ENUM
#include "MYRISCVXGenRegisterInfo.inc"

const MCPhysReg* MYRISCVXRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return CSR_LP32_SaveList;
}

const uint32_t* MYRISCVXRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                                          CallingConv::ID) const {
  return CSR_LP32_RegMask;
}

BitVector MYRISCVXRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  // zero, ra, fp, sp, gp, tp are reserved, thus not used by register allocator
  static const uint16_t ReservedCPURegs[] = {
    MYRISCVX::ZERO, MYRISCVX::RA, MYRISCVX::FP, MYRISCVX::SP, MYRISCVX::GP, MYRISCVX::TP
  };
  BitVector Reserved(getNumRegs());

  for (unsigned i = 0; i < array_lengthof(ReservedCPURegs); ++i)
    Reserved.set(ReservedCPURegs[i]);

  return Reserved;
}

bool MYRISCVXRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                              int SPAdj, unsigned FIOperandNum,
                                              RegScavenger *RS) const {
  // TODO
  return true;
}
