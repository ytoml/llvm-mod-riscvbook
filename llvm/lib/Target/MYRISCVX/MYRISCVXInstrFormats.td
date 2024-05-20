// @{ MYRISCVXInstrFormats_Formats
class Format<bits<3> val> {
  bits<3> Value = val;
}

def Pseudo : Format<0>;
def FrmR   : Format<1>;
def FrmI   : Format<2>;
def FrmS   : Format<3>;
def FrmU   : Format<4>;
def FrmB   : Format<5>;
def FrmJ   : Format<6>;
// @} MYRISCVXInstrFormats_Formats

class MYRISCVXInst<dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin, Format f>: Instruction
{
  field bits<32> Inst;
  Format Form = f;
  let Namespace = "MYRISCVX";

  bits<7> Opcode = 0;

  let Inst{6-0} = Opcode;
  let OutOperandList = outs;
  let InOperandList = ins;

  let AsmString = asmstr;
  // NOTE: ? the pattern that generates the instruction from LLVM IR
  let Pattern = pattern;
  let Itinerary = itin;

  bits<3> FormBits = Form.Value;

  // Should be kept in sync with MYRISCVXInstrInfo.h
  let TSFlags{2-0} = FormBits;

  let DecoderNamespace = "MYRISCXV";
  field bits<32> SoftFail = 0;
}

// ===---------------------------------------------------------------------===//
// R-type instructions class in MYRISCVX: <|funct7|rs2|rs1|funct3|rd|opcode|>
// ===---------------------------------------------------------------------===//
class MYRISCVX_R<
    bits<7> opcode, bits<3> funct3, bits<7> funct7,
    dag outs, dag ins, string asmstr,
    list<dag> pattern, InstrItinClass itin>: MYRISCVXInst<outs, ins, asmstr, pattern, itin, FrmR>
{
  bits<5> rd;
  bits<5> rs1;
  bits<5> rs2;

  let Inst{31-25} = funct7;
  let Inst{24-20} = rs2;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = rd;
  let Inst{6-0} = opcode;
}

// ===---------------------------------------------------------------------===//
// I-type instructions class in MYRISCVX: <|imm[11:0]|rs1|funct3|rd|opcode|>
// ===---------------------------------------------------------------------===//
class MYRISCVX_I<
    bits<7> opcode, bits<3> funct3,
    dag outs, dag ins, string asmstr,
    list<dag> pattern, InstrItinClass itin>: MYRISCVXInst<outs, ins, asmstr, pattern, itin, FrmI>
{
  bits<5> rd;
  bits<5> rs1;
  bits<12> simm12;

  let Inst{31-20} = simm12;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = rd;
  let Inst{6-0} = opcode;
}

// ===---------------------------------------------------------------------===//
// S-type instructions class in MYRISCVX: <|imm[11:5]|rs2|rs1|funct3|imm[4:0]|opcode|>
// ===---------------------------------------------------------------------===//
class MYRISCVX_S<
    bits<7> opcode, bits<3> funct3,
    dag outs, dag ins, string asmstr,
    list<dag> pattern, InstrItinClass itin>: MYRISCVXInst<outs, ins, asmstr, pattern, itin, FrmS>
{
  bits<5> rs1;
  bits<5> rs2;
  bits<12> simm12;

  let Inst{31-25} = simm12{11-5};
  let Inst{24-20} = rs2;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = simm12{4-0};
  let Inst{6-0} = opcode;
}

// ===---------------------------------------------------------------------===//
// U-type instructions class in MYRISCVX: <|imm[31:12]|rd|opcode|>
// ===---------------------------------------------------------------------===//
class MYRISCVX_U<
    bits<7> opcode,
    dag outs, dag ins, string asmstr,
    list<dag> pattern, InstrItinClass itin>: MYRISCVXInst<outs, ins, asmstr, pattern, itin, FrmU>
{
  bits<5> rd;
  bits<20> imm;

  let Inst{31-12} = imm;
  let Inst{11-7} = rd;
  let Inst{6-0} = opcode;
}

// ===---------------------------------------------------------------------===//
// B-type instructions class in MYRISCVX: <|imm[12]|imm[10:5]|rs2|rs1|funct3|imm[4:1]|imm[11]|opcode|>
// ===---------------------------------------------------------------------===//
class MYRISCVX_B<
    bits<7> opcode, bits<3> funct3,
    dag outs, dag ins, string asmstr,
    list<dag> pattern, InstrItinClass itin>: MYRISCVXInst<outs, ins, asmstr, pattern, itin, FrmB>
{
  bits<5> rs1;
  bits<5> rs2;
  // actually 13 bits: imm = imm12 << 1
  bits<12> imm12;

  let Inst{31} = imm12{11};
  let Inst{30-25} = imm12{9-4};
  let Inst{24-20} = rs2;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-8} = imm12{3-0};
  let Inst{7} = imm12{10};
  let Inst{6-0} = opcode;
}

// ===---------------------------------------------------------------------===//
// J-type instructions class in MYRISCVX: <|imm[20]|imm[10:1]|imm[11]|imm[19:12]|rd|opcode|>
// ===---------------------------------------------------------------------===//
class MYRISCVX_J<
    bits<7> opcode,
    dag outs, dag ins, string asmstr,
    list<dag> pattern, InstrItinClass itin>: MYRISCVXInst<outs, ins, asmstr, pattern, itin, FrmJ>
{
  bits<5> rd;
  // actually 21 bits: imm = imm20 << 1
  bits<20> imm20;

  let Inst{31} = imm20{19};
  let Inst{30-21} = imm20{9-0};
  let Inst{20} = imm20{10};
  let Inst{19-12} = imm20{18-11};
  let Inst{11-7} = rd;
  let Inst{6-0} = opcode;
}