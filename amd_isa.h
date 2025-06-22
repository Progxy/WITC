#ifndef _AMD_ISA_
#define _AMD_ISA_

// TODO: Find a better ordering for the instructions: like alphabetical?
static const Instruction instructions[] = {
	{
		.opcode = 0x0F0B,
		.mnemonic = "ud2",
		.expect_modrm = FALSE,
		.dynamic_operands_size = FALSE,
		.first_operand = NONE,
		.second_operand = NONE
	},
	{
		.opcode = 0x9B,
		.mnemonic = "wait",
		.expect_modrm = FALSE,
		.dynamic_operands_size = FALSE,
		.first_operand = NONE,
		.second_operand = NONE
	},
	{
		.opcode = 0xDBE3,
		.mnemonic = "fninit",
		.expect_modrm = FALSE,
		.dynamic_operands_size = FALSE,
		.first_operand = NONE,
		.second_operand = NONE
	},
	{
		.opcode = 0x9BBDE3,
		.mnemonic = "finit",
		.expect_modrm = FALSE,
		.dynamic_operands_size = FALSE,
		.first_operand = NONE,
		.second_operand = NONE
	},
	{
		.opcode = 0xF4,
		.mnemonic = "hlt",
		.expect_modrm = FALSE,
		.dynamic_operands_size = FALSE,
		.first_operand = NONE,
		.second_operand = NONE
	},
	{
		.opcode = 0xFA,
		.mnemonic = "cli",
		.expect_modrm = FALSE,
		.dynamic_operands_size = FALSE,
		.first_operand = NONE,
		.second_operand = NONE
	},
	{
		.opcode = 0xC9,
		.mnemonic = "leave",
		.expect_modrm = FALSE,
		.dynamic_operands_size = FALSE,
		.first_operand = NONE,
		.second_operand = NONE
	},
	{
		.opcode = 0xC3,
		.mnemonic = "ret",
		.expect_modrm = FALSE,
		.dynamic_operands_size = FALSE,
		.first_operand = NONE,
		.second_operand = NONE
	},
	{
		.opcode = 0x90,
		.mnemonic = "nop",
		.expect_modrm = FALSE,
		.dynamic_operands_size = FALSE,
		.first_operand = NONE,
		.second_operand = NONE
	},
	{
		.opcode = 0xCF,
		.mnemonic = "iret",
		.expect_modrm = FALSE,
		.dynamic_operands_size = TRUE,
		.default_operand_size = DEFAULT,
		.first_operand = NONE,
		.second_operand = NONE
	},
	{
		.opcode = 0xE7,
		.mnemonic = "out",
		.expect_modrm = FALSE,
		.default_operand_size = DEFAULT,
		.first_operand = IMM_8,
		.max_first_operand_size = IMM_8,
		.second_operand = DEFAULT_REG,
		.max_sec_operand_size= DEFAULT_REG,
		.default_reg = "rax"
	},
	{
		.opcode = 0xE8,
		.mnemonic = "call",
		.expect_modrm = FALSE,
		.default_operand_size = DEFAULT,
		.first_operand = IMM_32,
		.max_first_operand_size = IMM_32,
	},
	{
		.opcode = 0xC6,
		.mnemonic = "mov",
		.use_opcode_reg_dist = TRUE,
		.opcode_reg = 0x00,
		.expect_modrm = TRUE,
		.default_operand_size = BIT_8,
		.first_operand = REG_MEM_8,
		.max_first_operand_size = REG_MEM_8,
		.second_operand = IMM_8,
		.max_sec_operand_size = IMM_8
	},
	{
		.opcode = 0xC7,
		.mnemonic = "mov",
		.expect_modrm = TRUE,
		.dynamic_operands_size = TRUE,
		.default_operand_size = DEFAULT,
		.first_operand = REG_MEM_32,
		.max_first_operand_size = REG_MEM_64,
		.second_operand = IMM_32,
		.max_sec_operand_size = IMM_32
	},
	{
		.opcode = 0x88,
		.mnemonic = "mov",
		.expect_modrm = TRUE,
		.dynamic_operands_size = TRUE,
		.default_operand_size = BIT_8,
		.first_operand = REG_MEM_8,
		.max_first_operand_size = REG_MEM_8,
		.second_operand = REG_8,
		.max_sec_operand_size = REG_8
	},
	{
		.opcode = 0x89,
		.mnemonic = "mov",
		.expect_modrm = TRUE,
		.dynamic_operands_size = TRUE,
		.default_operand_size = DEFAULT,
		.first_operand = REG_MEM_32,
		.max_first_operand_size = REG_MEM_64,
		.second_operand = REG_32,
		.max_sec_operand_size = REG_64
	},
	{
		.opcode = 0x8B,
		.mnemonic = "mov",
		.expect_modrm = TRUE,
		.dynamic_operands_size = TRUE,
		.default_operand_size = DEFAULT,
		.first_operand = REG_32,
		.max_first_operand_size = REG_64,
		.second_operand = REG_MEM_32,
		.max_sec_operand_size = REG_MEM_64
	},
	{
		.opcode = 0xB8,
		.mnemonic = "mov",
		.expect_modrm = FALSE,
		.dynamic_operands_size = TRUE,
		.default_operand_size = DEFAULT,
		.first_operand = REG_32,
		.max_first_operand_size = REG_64,
		.second_operand = IMM_32,
		.max_sec_operand_size = IMM_64,
		.embedded_reg = TRUE
	},
	{
		.opcode = 0x8D,
		.mnemonic = "lea",
		.expect_modrm = TRUE,
		.dynamic_operands_size = TRUE,
		.default_operand_size = DEFAULT,
		.first_operand = REG_32,
		.max_first_operand_size = REG_64,
		.second_operand = MEM_32,
		.max_sec_operand_size = MEM_64
	},
	{
		.opcode = 0x0FB6,
		.mnemonic = "movzxb",
		.expect_modrm = TRUE,
		.default_operand_size = DEFAULT,
		.first_operand = REG_32,
		.max_first_operand_size = REG_64,
		.second_operand = REG_MEM_8,
		.max_sec_operand_size = REG_MEM_8
	},
	{
		.opcode = 0x0FB7,
		.mnemonic = "movzxw",
		.expect_modrm = TRUE,
		.default_operand_size = DEFAULT,
		.first_operand = REG_32,
		.max_first_operand_size = REG_64,
		.second_operand = REG_MEM_16,
		.max_sec_operand_size = REG_MEM_16
	},
	{
		.opcode = 0x50,
		.mnemonic = "push",
		.expect_modrm = FALSE,
		.dynamic_operands_size = TRUE,
		.default_operand_size = BIT_64,
		.first_operand = REG_32,
		.max_first_operand_size = REG_64,
		.second_operand = NONE,
		.embedded_reg = TRUE
	},
	{
		.opcode = 0x58,
		.mnemonic = "pop",
		.expect_modrm = FALSE,
		.dynamic_operands_size = TRUE,
		.default_operand_size = BIT_64,
		.first_operand = REG_32,
		.max_first_operand_size = REG_64,
		.second_operand = NONE,
		.embedded_reg = TRUE
	},
	{
		.opcode = 0x83,
		.mnemonic = "sub",
		.use_opcode_reg_dist = TRUE,
		.opcode_reg = 0x05,
		.expect_modrm = TRUE,
		.dynamic_operands_size = TRUE,
		.default_operand_size = DEFAULT,
		.first_operand = REG_32,
		.max_first_operand_size = REG_64,
		.second_operand = IMM_8,
		.max_sec_operand_size = IMM_8
	},
	{
		.opcode = 0x01,
		.mnemonic = "add",
		.expect_modrm = TRUE,
		.dynamic_operands_size = TRUE,
		.default_operand_size = DEFAULT,
		.first_operand = REG_MEM_32,
		.max_first_operand_size = REG_MEM_64,
		.second_operand = REG_32,
		.max_sec_operand_size = REG_64
	},
	{
		.opcode = 0x83,
		.mnemonic = "add",
		.use_opcode_reg_dist = TRUE,
		.opcode_reg = 0x00,
		.expect_modrm = TRUE,
		.dynamic_operands_size = TRUE,
		.default_operand_size = DEFAULT,
		.first_operand = REG_MEM_32,
		.max_first_operand_size = REG_MEM_64,
		.second_operand = IMM_8,
		.max_sec_operand_size = IMM_8
	},
	{
		.opcode = 0x83,
		.mnemonic = "cmp",
		.use_opcode_reg_dist = TRUE,
		.opcode_reg = 0x07,
		.expect_modrm = TRUE,
		.dynamic_operands_size = TRUE,
		.default_operand_size = DEFAULT,
		.first_operand = REG_32,
		.max_first_operand_size = REG_64,
		.second_operand = IMM_8,
		.max_sec_operand_size = IMM_8
	},
	{
		.opcode = 0x80,
		.mnemonic = "cmp",
		.use_opcode_reg_dist = TRUE,
		.opcode_reg = 0x07,
		.expect_modrm = TRUE,
		.default_operand_size = BIT_8,
		.dynamic_operands_size = TRUE,
		.first_operand = REG_MEM_8,
		.max_first_operand_size = REG_MEM_8,
		.second_operand = IMM_8,
		.max_sec_operand_size = IMM_8
	},
	{
		.opcode = 0x38,
		.mnemonic = "cmp",
		.expect_modrm = TRUE,
		.dynamic_operands_size = TRUE,
		.default_operand_size = BIT_8,
		.first_operand = REG_MEM_8,
		.max_first_operand_size = REG_MEM_8,
		.second_operand = REG_8,
		.max_sec_operand_size = REG_8
	},
	{
		.opcode = 0x39,
		.mnemonic = "cmp",
		.expect_modrm = TRUE,
		.dynamic_operands_size = TRUE,
		.default_operand_size = DEFAULT,
		.first_operand = REG_MEM_32,
		.max_first_operand_size = REG_MEM_64,
		.second_operand = REG_32,
		.max_sec_operand_size = REG_64
	},
	{
		.opcode = 0xC1,
		.mnemonic = "sal",
		.use_opcode_reg_dist = TRUE,
		.opcode_reg = 0x04,
		.expect_modrm = TRUE,
		.default_operand_size = BIT_64,
		.first_operand = REG_MEM_32,
		.max_first_operand_size = REG_MEM_64,
		.second_operand = IMM_8,
		.max_sec_operand_size = IMM_8
	},
	{
		.opcode = 0xC1,
		.mnemonic = "shr",
		.use_opcode_reg_dist = TRUE,
		.opcode_reg = 0x05,
		.expect_modrm = TRUE,
		.default_operand_size = BIT_64,
		.first_operand = REG_MEM_32,
		.max_first_operand_size = REG_MEM_64,
		.second_operand = IMM_8,
		.max_sec_operand_size = IMM_8
	},
	{
		.opcode = 0x09,
		.mnemonic = "or",
		.expect_modrm = TRUE,
		.dynamic_operands_size = TRUE,
		.default_operand_size = DEFAULT,
		.first_operand = REG_MEM_32,
		.max_first_operand_size = REG_MEM_64,
		.second_operand = REG_32,
		.max_sec_operand_size = REG_64
	},
	// TODO: The following should be better determined: "Many disassemblers prefer je after cmp instructions, and jz after operations like test"
	{
		.opcode = 0x74,
		.mnemonic = "je",
		.expect_modrm = FALSE,
		.dynamic_operands_size = FALSE,
		.default_operand_size = DEFAULT,
		.first_operand = IMM_8,
		.max_first_operand_size = IMM_8,
		.second_operand = NONE,
		.max_sec_operand_size = NONE
	},
	{
		.opcode = 0x0F84,
		.mnemonic = "je",
		.expect_modrm = FALSE,
		.dynamic_operands_size = FALSE,
		.default_operand_size = DEFAULT,
		.first_operand = IMM_32,
		.max_first_operand_size = IMM_32,
		.second_operand = NONE,
		.max_sec_operand_size = NONE
	},
	// TODO: The following should be better determined: "Many disassemblers prefer je after cmp instructions, and jz after operations like test"
	{
		.opcode = 0x75,
		.mnemonic = "jne",
		.expect_modrm = FALSE,
		.dynamic_operands_size = FALSE,
		.default_operand_size = DEFAULT,
		.first_operand = IMM_8,
		.max_first_operand_size = IMM_8,
		.second_operand = NONE,
		.max_sec_operand_size = NONE
	},
	// TODO: The following should be better determined: "Many disassemblers prefer je after cmp instructions, and jz after operations like test"
	{
		.opcode = 0x72,
		.mnemonic = "jb",
		.expect_modrm = FALSE,
		.dynamic_operands_size = FALSE,
		.default_operand_size = DEFAULT,
		.first_operand = IMM_8,
		.max_first_operand_size = IMM_8,
		.second_operand = NONE,
		.max_sec_operand_size = NONE
	},
	{
		.opcode = 0xEB,
		.mnemonic = "jmp",
		.expect_modrm = FALSE,
		.dynamic_operands_size = FALSE,
		.default_operand_size = DEFAULT,
		.first_operand = IMM_8,
		.max_first_operand_size = IMM_8,
		.second_operand = NONE,
		.max_sec_operand_size = NONE
	},
	{
		.opcode = 0xE9,
		.mnemonic = "jmp",
		.expect_modrm = FALSE,
		.dynamic_operands_size = FALSE,
		.default_operand_size = DEFAULT,
		.first_operand = IMM_32,
		.max_first_operand_size = IMM_32,
		.second_operand = NONE,
		.max_sec_operand_size = NONE
	},
	{
		.opcode = 0x84,
		.mnemonic = "test",
		.expect_modrm = TRUE,
		.default_operand_size = BIT_8,
		.first_operand = REG_MEM_8,
		.max_first_operand_size = REG_MEM_8,
		.second_operand = REG_8,
		.max_sec_operand_size = REG_8
	},
	{
		.opcode = 0x85,
		.mnemonic = "test",
		.expect_modrm = TRUE,
		.dynamic_operands_size = TRUE,
		.default_operand_size = DEFAULT,
		.first_operand = REG_MEM_32,
		.max_first_operand_size = REG_MEM_64,
		.second_operand = REG_32,
		.max_sec_operand_size = REG_64
	}
};

#endif //_AMD_ISA_

