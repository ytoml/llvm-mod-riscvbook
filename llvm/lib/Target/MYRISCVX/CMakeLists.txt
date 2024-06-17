add_llvm_component_group(MYRISCVX)

set(LLVM_TARGET_DEFINITIONS MYRISCVX.td)

# from MYRISCVXRegisterInfo.td
tablegen(LLVM MYRISCVXGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM MYRISCVXGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM MYRISCVXGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM MYRISCVXGenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM MYRISCVXCallingConv.td -gen-callingconv)

add_public_tablegen_target(MYRISCVXCommonTableGen)

# TODO: add others (instruction decodor, register decoder, etc.)
add_llvm_target(MYRISCVXCodeGen
  MYRISCVXTargetMachine.cpp
)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)