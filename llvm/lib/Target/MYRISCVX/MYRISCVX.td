
include "llvm/Target/Target.td"



// Enable FeatureRV64 when cpu-rv64 is selected
def FeatureRV64 : SubtargetFeature<"64bit", "IsRV64", "true", "RV64 support">;

def : ProcessorModel<"cpu-rv32", NoSchedModel, []>;
def : ProcessorModel<"cpu-rv64", NoSchedModel, [FeatureRV64]>;


// ===---------------------------------------------------------------------===//
// target dependent interfaces
// ===---------------------------------------------------------------------===//
def IsRV64 : Predicate<"Subtarget->is64Bit()">,
              AssemblerPredicate<(all_of FeatureRV64), "RV64 Mode">;
def IsRV32 : Predicate<"!Subtarget->is32Bit()">,
              AssemblerPredicate<(all_of (not FeatureRV64)), "RV32 Mode">;

// Switch
def RV64 : HwMode<"+64bit", [IsRV64]>;
def RV32 : HwMode<"-64bit", [IsRV32]>;

// "include" must follow the definition of RV64 and RV32 (because they use them).
include "MYRISCVXRegisterInfo.td"
include "MYRISCVXSchedule.td"
include "MYRISCVXInstrInfo.td"

def MYRISCVXInstrInfo : InstrInfo;

def MYRISCVX : Target {
  let InstructionSet = MYRISCVXInstrInfo;
}