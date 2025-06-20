#ifndef _WITC_H_
#define _WITC_H_

#include "./utils.h"

typedef enum OperandType { NONE = 0, DEFAULT_REG, REG_8, REG_16, REG_32, REG_64, MEM_8, MEM_16, MEM_32, MEM_64, REG_MEM_8, REG_MEM_16, REG_MEM_32, REG_MEM_64, IMM_8, IMM_16, IMM_32, IMM_64 } OperandType;

#define REG_MASK 0x38
#define MOD_MASK 0xC0
#define RM_MASK  0x07

#define IS_IMM(val)     ((val) >= IMM_8     && (val) <= IMM_64)
#define IS_REG(val)     ((val) >= REG_8     && (val) <= REG_64)
#define IS_MEM(val)     ((val) >= MEM_8     && (val) <= MEM_64)
#define IS_REG_MEM(val) ((val) >= REG_MEM_8 && (val) <= REG_MEM_64)
#define BIT_8_TYPE(val)                              \
	(IS_IMM(val) ? IMM_8 :                           \
		(IS_REG(val) ? REG_8 :                       \
			(IS_MEM(val) ? MEM_8 :                   \
				(IS_REG_MEM(val) ? REG_MEM_8 : NONE) \
			)                                        \
		)                                            \
	)

// TODO: Instead of DEFAULT should put 'BIT_32' for consistency
typedef enum OperandSize { BIT_16 = 0, DEFAULT, BIT_64, BIT_8 } OperandSize;
const int operand_effective_size_increment[] = { -1, 0, 1, -2 };
const char suffixes[] = { 'w', 'd', 'q', 'b' };

typedef struct PACKED_STRUCT Rex {
	u8 b: 1;
	u8 x: 1;
	u8 r: 1;
	u8 w: 1;
	u8 res: 4;
} Rex;

typedef struct Instruction {
	u64 opcode;
	bool use_opcode_reg_dist;
	u8 opcode_reg;
	char* mnemonic;
	bool expect_modrm;
	bool dynamic_operands_size;
	OperandSize default_operand_size;
	OperandType first_operand;
	OperandType max_first_operand_size;
	OperandType second_operand;
	OperandType max_sec_operand_size;
	char* default_reg;
	bool embedded_reg;
} Instruction;

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
		.first_operand = NONE,
		.second_operand = NONE,
		.embedded_reg = TRUE
	},
	{
		.opcode = 0x58,
		.mnemonic = "pop",
		.expect_modrm = FALSE,
		.dynamic_operands_size = TRUE,
		.default_operand_size = BIT_64,
		.first_operand = NONE,
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


static const char* regs[4][16] = {
	{ "ax", "cx", "dx", "bx", "sp", "bp", "si", "di","r8w", "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w" },
	{ "eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi", "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d" },
	{ "rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15" },
	{ "al", "cl", "dl", "bl", "sp", "bp", "sl", "dl", "r8b", "r9b", "r10b", "r11b", "r12b", "r13b", "r14b", "r15b" }
};

// ---------------------------------------------------------------
static inline int simple_ins_match(const u8* machine_data, const u64 size, u64* match_ins_size) {
	u64 opcode = *machine_data++;
	for (; *match_ins_size <= size; ++(*match_ins_size)) {
		for (u64 i = 0; i < ARR_SIZE(instructions); ++i) {
			if (opcode == instructions[i].opcode) {
				if (instructions[i].use_opcode_reg_dist && instructions[i].opcode_reg != ((*machine_data & 0x38) >> 3)) continue;
				return i;
			// TODO: Not considering the possibility of a range opcode matched with also opcode_reg distinguisher
			} else if (instructions[i].embedded_reg && (opcode >= instructions[i].opcode && opcode <= instructions[i].opcode + 0x07)) return i;
		}
		opcode = (opcode << 8) | *machine_data++;
	}
	return -1;
}

static int decode_modrm_operand(bool is_first_operand, OperandType operand, OperandSize operand_size, u8 mod, u8 rm, u8 reg, const u8* machine_data, const Instruction ins, InsInfo* ins_info, u64* ins_size) {
	int pos = str_len(ins_info -> ins_str);
	if (pos == MAX_DISASM_INS_LEN) return -1;
	set_char(ins_info -> ins_str + pos, ' ');
	
	if (IS_MEM(operand) || IS_REG_MEM(operand)) {
		if (mod == 0x03) str_cpy(ins_info -> ins_str + pos + 1, regs[operand_size][rm]);
		else {
			DEBUG("mod: 0x%X, rm: 0x%X, reg: 0x%X", mod, rm, reg);
			u8 displacement_size = mod * mod;
			bool only_displacement = mod == 0 && rm == 0x05;
			
			set_char(ins_info -> ins_str + pos + 1, '[');
			
			if (!only_displacement) str_cpy(ins_info -> ins_str + pos + 2, regs[2][rm]);
			else displacement_size = 4;

			if (rm == 0x04) {
				DEBUG("machine_data: 0x%X", *(machine_data - 1));
				TODO("implement SIB handling.");
				return -1;
			}

			int displacement = 0;
			mem_cpy(&displacement, machine_data, displacement_size);
			if (displacement_size == 1) displacement = *((char*) &displacement);

			machine_data += displacement_size, (*ins_size) += displacement_size;
			
			if (displacement != 0) {
				if (only_displacement && displacement < 0) mem_set(ins_info -> ins_str + str_len(ins_info -> ins_str), '-', sizeof(char));
				else if (displacement < 0) str_cpy(ins_info -> ins_str + str_len(ins_info -> ins_str), " - ");
				else str_cpy(ins_info -> ins_str + str_len(ins_info -> ins_str), " + ");
				
				displacement = ABS(displacement);
				
				byte_str_into_dec_val(ins_info -> ins_str + str_len(ins_info -> ins_str), (u8*) &displacement, displacement_size);
				set_char(ins_info -> byte_ins + str_len(ins_info -> byte_ins), ' ');
				byte_str_into_hex_str(ins_info -> byte_ins + str_len(ins_info -> byte_ins), machine_data - displacement_size, displacement_size);
			}

			set_char(ins_info -> ins_str + str_len(ins_info -> ins_str), ']');
		}
	} else if (IS_REG(operand)) str_cpy(ins_info -> ins_str + pos + 1, regs[operand_size][reg]);
	else if (IS_IMM(operand)) {
		u8 imm_size = 1U << (operand - IMM_8);
		byte_str_into_hex_val(ins_info -> ins_str + pos + 1, machine_data, imm_size);
		set_char(ins_info -> byte_ins + str_len(ins_info -> byte_ins), ' ');
		byte_str_into_hex_str(ins_info -> byte_ins + str_len(ins_info -> byte_ins), machine_data, imm_size);
		(*ins_size) += imm_size;
	} else if (operand == DEFAULT_REG) str_cpy(ins_info -> ins_str + pos + 1, ins.default_reg);

	if (is_first_operand) { 
		pos = str_len(ins_info -> ins_str);
		if (pos == MAX_DISASM_INS_LEN) return -1;
		set_char(ins_info -> ins_str + pos, ',');
	}

	return 0;
}

static int decode_operand(bool is_first_operand, OperandType operand, OperandSize operand_size, const Instruction ins, InsInfo* ins_info, const u8* machine_data, u64* ins_size) {
	int pos = str_len(ins_info -> ins_str);
	if (pos == MAX_DISASM_INS_LEN) return -1;
	set_char(ins_info -> ins_str + pos, ' ');
	
	// TODO: Check if it is true that only the first operand can be the embedded reg
	if (ins.embedded_reg && is_first_operand) {
		u8 reg = *(machine_data - 1) & 0x07;
		str_cpy(ins_info -> ins_str + pos + 1, regs[operand_size][reg]);
	 } else if (IS_IMM(operand)) {
		u8 imm_size = 1U << (operand - IMM_8);
		byte_str_into_hex_val(ins_info -> ins_str + pos + 1, machine_data, imm_size);
		set_char(ins_info -> byte_ins + str_len(ins_info -> byte_ins), ' ');
		byte_str_into_hex_str(ins_info -> byte_ins + str_len(ins_info -> byte_ins), machine_data, imm_size);
		(*ins_size) += imm_size;
	} else if (operand == DEFAULT_REG) str_cpy(ins_info -> ins_str + pos + 1, ins.default_reg);

	if (is_first_operand && ins.second_operand != NONE) { 
		pos = str_len(ins_info -> ins_str);
		if (pos == MAX_DISASM_INS_LEN) return -1;
		set_char(ins_info -> ins_str + pos, ',');
	}

	return 0;
}

static int decode_into_mnemonic(Instruction ins, OperandSize operand_size, const u8** machine_data, const Rex rex, InsInfo* ins_info, u64* ins_size) {
	if (ins.expect_modrm) {
		u8 reg = (**machine_data & REG_MASK) >> 3 | (rex.r << 3);
		u8 mod = (**machine_data & MOD_MASK) >> 6;
		u8 rm = (**machine_data & RM_MASK) | (rex.b << 3);
		
		set_char(ins_info -> byte_ins + str_len(ins_info -> byte_ins), ' ');
		byte_str_into_hex_str(ins_info -> byte_ins + str_len(ins_info -> byte_ins), *machine_data, 1);
		
		// Increase size as we've read the ModRM byte
		(*machine_data)++;
		(*ins_size)++;
		
		OperandType first_operand = ins.first_operand + ins.dynamic_operands_size * operand_effective_size_increment[operand_size];
		OperandType second_operand = ins.second_operand + ins.dynamic_operands_size * operand_effective_size_increment[operand_size];
		
		first_operand = CLAMP(first_operand,  BIT_8_TYPE(ins.first_operand),  ins.max_first_operand_size);
		second_operand = CLAMP(second_operand, BIT_8_TYPE(ins.second_operand), ins.max_sec_operand_size);

		if (decode_modrm_operand(TRUE, first_operand, operand_size, mod, rm, reg, *machine_data, ins, ins_info, ins_size) < 0) return -1;
		if (decode_modrm_operand(FALSE, second_operand, operand_size, mod, rm, reg, *machine_data, ins, ins_info, ins_size) < 0) return -1;
		return 0;
	} 	 
	
	if (ins.first_operand != NONE) {
		OperandType first_operand = MIN(ins.first_operand + (ins.dynamic_operands_size * operand_effective_size_increment[operand_size]), ins.max_first_operand_size);
		if (decode_operand(TRUE, first_operand, operand_size, ins, ins_info, *machine_data, ins_size) < 0) return -1;
	}
	
	if (ins.second_operand != NONE) {
		OperandType second_operand = MIN(ins.second_operand + (ins.dynamic_operands_size * operand_effective_size_increment[operand_size]), ins.max_sec_operand_size);
		if (decode_operand(FALSE, second_operand, operand_size, ins, ins_info, *machine_data, ins_size) < 0) return -1;
	 }

	return 0;
}

static int check_prefix(OperandSize* operand_size, Rex* rex, InsInfo* ins_info, const u64 size, u8 prefix, u64* ins_size, const u8** machine_data) {
	if (prefix >= 0x40 && prefix <= 0x4F) {
		*rex = *CAST_PTR(&prefix, Rex);
		if (rex -> w) *operand_size = BIT_64;
		DEBUG("Rex: { w: %u, r: %u, x: %u, b: %u}", rex -> w, rex -> r, rex -> x, rex -> b);
		if (*ins_size >= size) return -1;
	} else if (prefix == 0x66) {
		DEBUG("66h prefix found");
		*operand_size = BIT_16;
		if (*ins_size >= size) return -1;
	} else return 0;
	
	(*machine_data)++, (*ins_size)++;
	
	byte_str_into_hex_str(ins_info -> byte_ins, *machine_data - 1, 1);
	set_char(ins_info -> byte_ins + 2, ' ');
	
	return 0;
}

static int decode_instruction(const u8* machine_data, const u64 size, InsInfo* ins_info) {
	u8 prefix = *machine_data;
	u64 ins_size = 0;

	Rex rex = {0};
	OperandSize operand_size = DEFAULT;
	if (check_prefix(&operand_size, &rex, ins_info, size, prefix, &ins_size, &machine_data) < 0) return -1;

	// TODO: The following should be better factored inside the same ins_matching function: which is too simple, and does not take into account 
	// the single instruction multi functionality like the "finit = wait + fninit" case
	u64 match_ins_size = 1;
	int ret = simple_ins_match(machine_data, size - ins_size, &match_ins_size);
	
	machine_data += match_ins_size;

	if (ret < 0) {
		byte_str_into_hex_str(ins_info -> byte_ins, (u8*) machine_data - match_ins_size, MIN(8, match_ins_size));
		return ret;
	}
	
	ins_size += match_ins_size;
	
	const Instruction ins = instructions[ret];
	byte_str_into_hex_str(ins_info -> byte_ins + str_len(ins_info -> byte_ins), (u8*) machine_data - match_ins_size, match_ins_size);
	str_cpy(ins_info -> ins_str, ins.mnemonic);
	
	if (ins.dynamic_operands_size) {
		if (operand_size == DEFAULT) operand_size = ins.default_operand_size;
		set_char(ins_info -> ins_str + str_len(ins_info -> ins_str), suffixes[operand_size]);
	}

	if (decode_into_mnemonic(ins, operand_size, &machine_data, rex, ins_info, &ins_size) < 0) return -1;

	return ins_size;
}

#endif //_WITC_H_

