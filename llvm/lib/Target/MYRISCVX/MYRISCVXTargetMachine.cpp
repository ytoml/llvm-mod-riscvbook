//===-- MYRISCVXTargetMachine.cpp - Define TargetMachine for MYRISCVX -------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Implements the info about MYRISCVX target spec.
//
//===----------------------------------------------------------------------===//

#include "MYRISCVX.h"
#include "MYRISCVXTargetMachine.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "MYRISCVX"

extern "C" void LLVMInitializeMYRISCVXTarget() {
  RegisterTargetMachine<MYRISCVX32TargetMachine> X(getTheMYRISCVXTarget32());
  RegisterTargetMachine<MYRISCVX64TargetMachine> Y(getTheMYRISCVXTarget64());
}

MYRISCVXTargetMachine::MYRISCVXTargetMachine(const Target &T, const Triple &TT,
                                             StringRef CPU, StringRef FS,
                                             const TargetOptions &Options,
                                             Optional<Reloc::Model> RM,
                                             Optional<CodeModel::Model> CM,
                                             CodeGenOpt::Level OL, bool JIT)
    : LLVMTargetMachine(T, computeDataLayrout(TT, CPU, Options), TT, CPU, FS,
                        Options, getEffectiveRelocModel(JIT, RM), getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<MYRISCVXTargetObjectFile>()),
      ABI(MYRISCVXABIInfo::computeTargetABI(Options.MCOptions.getABIName())),
      DefaultSubtarget(TT, CPU, CPU, FS, *this) {
  initAsmInfo();
}

MYRISCVXTargetMachine::~MYRISCVXTargetMachine() {}

void MYRISCVX32TargetMachine::anchor() {}

MYRISCVX32TargetMachine::MYRISCVX32TargetMachine(const Target &T, const Triple &TT,
                                                 StringRef CPU, StringRef FS,
                                                 const TargetOptions &Options,
                                                 Optional<Reloc::Model> RM,
                                                 Optional<CodeModel::Model> CM,
                                                 CodeGenOpt::Level OL, bool JIT)
    : MYRISCVXTargetMachine(T, TT, CPU, FS, Options, RM, CM, OL, JIT) {}

void MYRISCVX64TargetMachine::anchor() {}

MYRISCVX64TargetMachine::MYRISCVX64TargetMachine(const Target &T, const Triple &TT,
                                                 StringRef CPU, StringRef FS,
                                                 const TargetOptions &Options,
                                                 Optional<Reloc::Model> RM,
                                                 Optional<CodeModel::Model> CM,
                                                 CodeGenOpt::Level OL, bool JIT)
    : MYRISCVXTargetMachine(T, TT, CPU, FS, Options, RM, CM, OL, JIT) {}

namespace {
class MYRISCVXPassConfig : public TargetPassConfig {
  public:
    MYRISCVXPassConfig(MYRISCVXTargetMachine &TM, PassManagerBase &PM)
        : TargetPassConfig(TM, PM) {}

    MYRISCVXTargetMachine &getMYRISCVXTargetMachine() const {
      return getTM<MYRISCVXTargetMachine>();
    }
};
}

TargetPassConfig *MYRISCVXTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new MYRISCVXPassConfig(*this, PM);
} 