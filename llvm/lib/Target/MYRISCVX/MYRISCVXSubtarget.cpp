#include "MYRISCVXSubtarget.h"

#include "MYRISCVXMachineFunction.h"
#include "MYRISCVX.h"
#include "MYRISCVXRegisterInfo.h"

#include "MYRISCVXTargetMachine.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "MYRISCVX-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "MYRISCVXGenSubtargetInfo.inc"

extern bool FixGlobalBaseReg;

void MYRISCVXSubtarget::anchor() {}

MYRISCVXSubtarget::MYRISCVXSubtarget(const Triple &TT, StringRef &CPU, StringRef &TuneCPU,
                                      StringRef FS,
                                      const MYRISCXVTargetMachine &_TM)
  : MYRISCVXGenSubtargetInfo(TT, CPU, TuneCPU, FS),
  TM(_TM),  TargetTriple(TT), TSInfo(),
  InstrInfo(),
  FrameLowering(initializeSubtargetDependencies(CPU, TuneCPU, FS, TM)),
  TLInfo(TM, *this), RegInfo(*this, getHwMode()) {}


MYRISCVXSubtarget &MYRISCVXSubtarget::initializeSubtargetDependencies(
  StringRef CPU,
  StringRef TuneCPU,
  StringRef FS,
  const TargetMachine &TM)
{
  if (TargetTriple.getArch() == Triple::myriscvx32) {
    if (CPU.empty() || CPU == "generic") {
      // align with ProcessorModel defined in MYRISCVX.td
      CPU = "cpu-rv32"
    }
  } else if (TargetTriple.getArch() == Triple::myriscvx64) {
    if (CPU.empty() || CPU == "generic") {
      CPU = "cpu-rv64"
    }
  } else {
    errs() << "!!!Error, TargetTriple.getArch() = " << TargetTriple.getArch() << "CPU = " << CPU << "\n";
    exit(0);
  }
  // Parse features from options passed to llc.
  ParseSubtargetFeatures(CPU, TuneCPU, FS);

  InstrItins = getInstrItineraryForCPU(CPU);
  if (IsRV64 == true) {
    RegType = MVT::i64;
  } else {
    RegType = MVT::i32;
  }
  return *this;
}