//===-- Cpu0TargetMachine.h - Define TargetMachine for Cpu0 -----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the Cpu0 specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MYRISCVX_MYRISCVXTARGETMACHINE_H
#define LLVM_LIB_TARGET_MYRISCVX_MYRISCVXTARGETMACHINE_H

#include "MCTargetDesc/MYRISCVXMCTargetDesc.h"
#include "MYRISCVXSubtarget.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class MYRISCVXTargetMachine : public LLVMTargetMachine {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  MYRISCVXABIInfo ABI;
  MYRISCVXSubtarget DefaultSubtarget;

  public:
    MYRISCVXTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                          StringRef FS, const TargetOptions &Options,
                          Optional<Reloc::Model> RM,
                          Optional<CodeModel::Model> CM,
                          CodeGenOpt::Level> OL, bool JIT);

    ~MYRISCVXTargetMachine() override;

    const MYRISCVXSubtarget *getSubtargetImpl(const Function &F) const override {
      return &DefaultSubtarget;
    }

    TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

    TargetLoweringObjectFile *getObjFileLowering() const override {
      return TLOF.get();
    }
  
  const MYRISCVXABIInfo &getABI() const { return ABI; }
};

class MYRISCVX32TargetMachine :  public MYRISCVXTargetMachine {
  virtual void anchor();
  public:
    MYRISCVX32TargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                            StringRef FS, const TargetOptions &Options,
                            Optional<Reloc::Model> RM,
                            Optional<CodeModel::Model> CM,
                            CodeGenOpt::Level> OL, bool JIT);
};

class MYRISCVX64TargetMachine :  public MYRISCVXTargetMachine {
  virtual void anchor();
  public:
    MYRISCVX64TargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                            StringRef FS, const TargetOptions &Options,
                            Optional<Reloc::Model> RM,
                            Optional<CodeModel::Model> CM,
                            CodeGenOpt::Level> OL, bool JIT);
};
}

#endif // LLVM_LIB_TARGET_MYRISCVX_MYRISCVXTARGETMACHINE_H