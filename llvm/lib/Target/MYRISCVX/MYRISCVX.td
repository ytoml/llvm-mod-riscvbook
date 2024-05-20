
include "llvm/Target/Target.td"

// Target dependent interface for MYRISCVX

// Switch
def RV64 : HwMode<"+64bit">;
def RV32 : HwMode<"-64bit">;

include "MYRISCVXRegisterInfo.td"
include "MYRISCVXInstrInfo.td"

def MYRISCVX : Target {
  let InstructionSet = MYRISCVXInstrInfo;
}

// Enable FeatureRV64 when cpu-rv64 is selected
def FeatureRV64 : SubtargetFeature<"64bit", "HasRV64", "false", "RV64 support">;
def : ProcessorModel<"cpu-rv32", NoSchedModel, []>
def : ProcessorModel<"cpu-rv64", NoSchedModel, [FeatureRV64]>
