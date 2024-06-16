include "MYRISCVXInstrFormats.td"


// @{ MYRISCVXInstrInfo_Operand_Definition_simm12
// 12ビットの即値オペランド
def simm12 : Operand<RegType>, ImmLeaf<RegType, [{return isInt<12>(Imm);}]>;
// @} MYRISCVXInstrInfo_Operand_Definition_simm12
// @{ MYRISCVXInstrInfo_Operand_Definition_simm20u
// 上位20ビットで下位12ビットが0の即値オペランド
def simm20u : Operand<RegType>, ImmLeaf<RegType, [{return isInt<32>(Imm) && !(Imm & 0x0fff);}]>;
// @} MYRISCVXInstrInfo_Operand_Definition_simm20u
// @{ MYRISCVXInstrInfo_Operand_Definition_simm32
// 32ビットの即値オペランド
def simm32: Operand<RegType>, ImmLeaf<RegType, [{return isInt<32>(Imm);}]>;
// @} MYRISCVXInstrInfo_Operand_Definition_simm32
//@} MYRISCVXInstrInfo_Operand_Definition

// ===---------------------------------------------------------------------===//
// Instructions specific format
// ===---------------------------------------------------------------------===//
class ArithLogicR<bits<7> opcode, bits<3> funct3, bits<7> funct7, string instr_asm, SDNode OpNode, RegisterClass RC> : 
  MYRISCVX_R<
    opcode, funct3, funct7, (outs RC:$rd), (ins RC:$rs1, RC:$rs2),
    !strconcat(instr_asm, "\t$rd, $rs1, $rs2"),
    [(set RC:$rd, (OpNode RC:$rs1, RC:$rs2))], IIAlu>
{
  let isReMaterializable = 1;
}

class ArithLogicI<bits<7> opcode, bits<3> funct3, string instr_asm, SDNode OpNode, Operand Od, RegisterClass RC> : 
  MYRISCVX_I<
    opcode, funct3, (outs RC:$rd), (ins RC:$rs1, Od:$simm12),
    !strconcat(instr_asm, "\t$rd, $rs1, $simm12"),
    [(set RC:$rd, (OpNode RC:$rs1, Od:$simm12))], IIAlu>
{
  let isReMaterializable = 1;
}

class ArithLogicU<bits<7> opcode, string instr_asm, Operand Od, RegisterClass RC> : 
  MYRISCVX_U<
    opcode, (outs RC:$rd), (ins Od:$imm20),
    !strconcat(instr_asm, "\t$rd, $imm20"),
    // LUI, AUIPC, etc. cannot be represented in a single form, thus [] is used
    [], IIAlu>
{
  let isReMaterializable = 1;
}

// Allocate GPR for operands
def ADDI: ArithLogicI<0b0010011, 0b000, "addi", add, simm12, GPR>;
def LUI: ArithLogicU<0b0110111, "lui", simm20u, GPR>;
def ADD: ArithLogicR<0b0110011, 0b000, 0b0000000, "add", add, GPR>;
def SUB: ArithLogicR<0b0110011, 0b000, 0b0100000, "sub", sub, GPR>;