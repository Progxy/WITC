#ifndef _WITC_H_
#define _WITC_H_

#include "./utils.h"

typedef enum OperandType { NONE = 0, REGISTER, REG_8, REG_16, REG_32, REG_64, MEMORY, MEM_8, MEM_16, MEM_32, MEM_64, IMMEDIATE, IMM_8, IMM_16, IMM_32, IMM_64 } OperandType;

#define IS_IMM(val) ((val) >= IMM_8 && (val) <= IMM_64)
#define IS_REG(val) ((val) >= REG_8 && (val) <= REG_64)
#define IS_MEM(val) ((val) >= MEM_8 && (val) <= MEM_64)

typedef struct Instruction {
	u64 opcode;
	char* mnemonic;
	bool expect_modrm;
	bool dynamic_operands_size;
	OperandType first_operand;
	OperandType max_first_operand_size;
	OperandType second_operand;
	OperandType max_sec_operand_size;
} Instruction;

static const Instruction instructions[] = {
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
		.opcode = 0xCF,
		.mnemonic = "iret",
		.expect_modrm = FALSE,
		.dynamic_operands_size = TRUE,
		.first_operand = NONE,
		.second_operand = NONE
	},
	{
		.opcode = 0xC7,
		.mnemonic = "mov",
		.expect_modrm = TRUE,
		.dynamic_operands_size = TRUE,
		.first_operand = REG_32,
		.max_first_operand_size = REG_64,
		.second_operand = IMM_32,
		.max_sec_operand_size = IMM_32
	},
	{
		.opcode = 0x89,
		.mnemonic = "mov",
		.expect_modrm = TRUE,
		.dynamic_operands_size = TRUE,
		.first_operand = REG_32,
		.max_first_operand_size = REG_64,
		.second_operand = REG_32,
		.max_sec_operand_size = REG_64
	}
};

typedef enum OperandSize { BIT_16, DEFAULT, BIT_64 } OperandSize;
const int operand_effective_size_increment[] = { -1, 0, 1};
const char suffixes[] = { 'w', 'd', 'q' };

typedef struct PACKED_STRUCT Rex {
	u8 res: 4;
	u8 w: 1;
	u8 r: 1;
	u8 x: 1;
	u8 b: 1;
} Rex;

// ---------------------------------------------------------------
static void bin_dump(u8* bin_data, u64 size) {
	printf(" -- Bin Dump (%llu bytes) -- \n", size);
	for (u64 i = 0; i < size; ++i) {
		if (i % 8 == 0) printf("  ");
		printf("0x%02X%c", bin_data[i], (i + 1) % 8 ? ' ': '\n');
		if ((((i + 1) % 8)) && (i == size - 1)) printf("\n");
	}
	printf(" -----------------------------\n");
	return;
}

static inline int simple_ins_match(const u64 opcode) {
	for (u64 i = 0; i < ARR_SIZE(instructions); ++i) {
		if (opcode == instructions[i].opcode) return i;
	}
	return -1;
}

static int decode_instruction(const u8* machine_data, const u64 size, InsInfo* ins_info) {
	u64 opcode = *machine_data++;
	u8 ins_size = 1;

	// TODO: The following should be inserted in a function factoring out the latter if statement
	// Instruction defaults to 32-bits, so this suffix is always present
	Rex rex = {0};
	OperandSize operand_size = DEFAULT;
	if (opcode >= 0x40 && opcode <= 0x4F) {
		rex = *((Rex*) &opcode);
		operand_size = BIT_64;
		DEBUG("Rex: { w: %u, r: %u, x: %u, b: %u}", rex.w, rex.r, rex.x, rex.b);
		if (ins_size >= size) return -1;
		opcode = *machine_data++, ins_size++;
	} else if (opcode == 0x66) {
		DEBUG("66h prefix found");
		operand_size = BIT_16;
		if (ins_size >= size) return -1;
		opcode = *machine_data++, ins_size++;
	}
	
	if (operand_size != DEFAULT) {
		byte_str_into_hex_str(ins_info -> byte_ins, machine_data - 2, 1, FALSE);
		// TODO: Should most probably introduce an append_str function
		mem_set(ins_info -> byte_ins + 2, ' ', sizeof(char));
	}

	// TODO: The following should be better factored inside the same ins_matching function: which is too simple, and does not take into account 
	// the single instruction multi functionality like the "finit = wait + fninit" case
	int ret = simple_ins_match(opcode);
	for (; ins_size < size && ret < 0; ++ins_size) {
		opcode = (opcode << 8) | *machine_data++;
		ret = simple_ins_match(opcode);
	}
	
	if (ret < 0) {
		byte_str_into_hex_str(ins_info -> byte_ins, (u8*) machine_data - ins_size, MIN(8, ins_size), FALSE);
		return ret;
	}

	// TODO: The following copy could be used to be customized in this situation instead of performing the hack below, for more consistency (like the calc of second_operand size)
	const Instruction ins = instructions[ret];

	// TODO: Should most probably introduce an append_str function
	byte_str_into_hex_str(ins_info -> byte_ins + str_len(ins_info -> byte_ins), (u8*) &opcode, ins_size, FALSE);
	str_cpy(ins_info -> ins_str, ins.mnemonic);
	if (ins.dynamic_operands_size) mem_set(ins_info -> ins_str + str_len(ins_info -> ins_str), suffixes[operand_size], sizeof(char));
	
	// TODO: The following should be put in another function maybe alongside another for SIB-decoding
	const char* regs[8] =  { "rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi" };
	const char* rms_m[8] =  { "rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi" };
	
	if (ins.expect_modrm) {
		u8 reg_mask = 0x38;
		if (rex.r) reg_mask |= 0x40;
		if (rex.b) reg_mask <<= 1;
		u8 reg = (*machine_data & reg_mask) >> (3 + rex.b);
		
		int pos = str_len(ins_info -> ins_str);
		if (pos == MAX_DISASM_INS_LEN) return ins_size;
		mem_set(ins_info -> ins_str + pos, ' ', sizeof(char));
		str_cpy(ins_info -> ins_str + pos + 1, regs[reg]);

		u8 mod_mask = 0xC0;
		if (rex.b) mod_mask <<= 1;
		if (rex.r) mod_mask <<= 1;
		u8 mod = (*machine_data & mod_mask) >> (6 + rex.r + rex.b);
		DEBUG("mod: 0x%X", mod);

		u8 rm_mask = 0x07;
		if (rex.b) rm_mask |= 0x08;
		u8 rm = *machine_data & rm_mask;
		
		// Increase size as we've read the ModRM byte
		ins_size++;
		
		OperandType second_operand = MIN(ins.second_operand + (ins.dynamic_operands_size * operand_effective_size_increment[operand_size]), ins.max_sec_operand_size);
		if (IS_IMM(second_operand)) {
			u8 imm_size = 1U << (second_operand - IMM_8);
			str_cpy(ins_info -> ins_str + str_len(ins_info -> ins_str), ", ");
			byte_str_into_hex_str(ins_info -> ins_str + str_len(ins_info -> ins_str), ++machine_data, imm_size, TRUE);
			ins_size += imm_size;
		} else if (mod == 0x03 && (IS_REG(second_operand) || IS_MEM(second_operand))) {
			int pos = str_len(ins_info -> ins_str);
			if (pos == MAX_DISASM_INS_LEN) return ins_size;
			str_cpy(ins_info -> ins_str + pos, ", ");
			str_cpy(ins_info -> ins_str + pos + 2, rms_m[rm]);
		}
	}

	return ins_size;
}

#endif //_WITC_H_

