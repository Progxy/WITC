#ifndef _WITC_H_
#define _WITC_H_

#include "./utils.h"

typedef enum OperandType { NONE = 0, REG_8, REG_16, REG_32, REG_64, MEM_8, MEM_16, MEM_32, MEM_64, IMM_8, IMM_16, IMM_32, IMM_64 } OperandType;

#define IS_IMM(val) ((val) >= IMM_8 && (val) <= IMM_64)
#define IS_REG(val) ((val) >= REG_8 && (val) <= REG_64)
#define IS_MEM(val) ((val) >= MEM_8 && (val) <= MEM_64)

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
	bool embedded_reg;
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
		.default_operand_size = DEFAULT,
		.first_operand = NONE,
		.second_operand = NONE
	},
	{
		.opcode = 0xC7,
		.mnemonic = "mov",
		.expect_modrm = TRUE,
		.dynamic_operands_size = TRUE,
		.default_operand_size = DEFAULT,
		.first_operand = REG_32,
		.max_first_operand_size = REG_64,
		.second_operand = IMM_32,
		.max_sec_operand_size = IMM_32
	},
	{
		.opcode = 0x88,
		.mnemonic = "mov",
		.expect_modrm = TRUE,
		.dynamic_operands_size = TRUE,
		.default_operand_size = BIT_8,
		.first_operand = REG_8,
		.max_first_operand_size = REG_8,
		.second_operand = REG_8,
		.max_sec_operand_size = REG_8
	},
	{
		.opcode = 0x89,
		.mnemonic = "mov",
		.expect_modrm = TRUE,
		.dynamic_operands_size = TRUE,
		.default_operand_size = DEFAULT,
		.first_operand = REG_32,
		.max_first_operand_size = REG_64,
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
		.second_operand = REG_32,
		.max_sec_operand_size = REG_64
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
		.mnemonic = "movzx",
		.expect_modrm = TRUE,
		.dynamic_operands_size = TRUE,
		.default_operand_size = DEFAULT,
		.first_operand = REG_32,
		.max_first_operand_size = REG_64,
		.second_operand = REG_8,
		.max_sec_operand_size = REG_8
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
	}
};

// ---------------------------------------------------------------
// TODO: Prettify the following print
static void bin_dump(u8* bin_data, u64 size) {
    printf("\t╔══════════════════════════════════════╗\n");
    printf("\t║         Bin Dump (%llu bytes)          ║\n", size);
    printf("\t╠══════════════════════════════════════╣\n");
    
    for (u64 i = 0; i < size; ++i) {
        if (i % 8 == 0) printf("\t║  0x%04llX: ", i);
        
        printf("%02X ", bin_data[i]);
        
        if ((i + 1) % 8 == 0 || i == size - 1) printf(" %*.s║\n", (int) (i == size - 1 ? 3 * (8 - ((i + 1) % 8) + 1) : 3), " ");
    }
    
    printf("\t╚══════════════════════════════════════╝\n\n");
	return;
}

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

static int decode_instruction(const u8* machine_data, const u64 size, InsInfo* ins_info) {
	u8 prefix = *machine_data;
	u64 ins_size = 0;

	// TODO: The following should be inserted in a function factoring out the latter if statement
	// Instruction defaults to 32-bits, so this suffix is always present
	Rex rex = {0};
	OperandSize operand_size = DEFAULT;
	if (prefix >= 0x40 && prefix <= 0x4F) {
		rex = *((Rex*) (&prefix));
		operand_size = BIT_64;
		DEBUG("Rex: { w: %u, r: %u, x: %u, b: %u}", rex.w, rex.r, rex.x, rex.b);
		if (ins_size >= size) return -1;
		machine_data++, ins_size++;
	} else if (prefix == 0x66) {
		DEBUG("66h prefix found");
		operand_size = BIT_16;
		if (ins_size >= size) return -1;
		machine_data++, ins_size++;
	}
	
	if (operand_size != DEFAULT) {
		byte_str_into_hex_str(ins_info -> byte_ins, machine_data - 1, 1);
		// TODO: Should most probably introduce an append_str function
		mem_set(ins_info -> byte_ins + 2, ' ', sizeof(char));
	}

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
	
	// TODO: The following copy could be used to be customized in this situation instead of performing the hack below, for more consistency (like the calc of second_operand size)
	const Instruction ins = instructions[ret];

	// TODO: Should most probably introduce an append_str function
	byte_str_into_hex_str(ins_info -> byte_ins + str_len(ins_info -> byte_ins), (u8*) machine_data - match_ins_size, match_ins_size);
	str_cpy(ins_info -> ins_str, ins.mnemonic);
	if (ins.dynamic_operands_size) {
		if (operand_size == DEFAULT) operand_size = ins.default_operand_size;
		mem_set(ins_info -> ins_str + str_len(ins_info -> ins_str), suffixes[operand_size], sizeof(char));
	}

	// TODO: The following should be put in another function maybe alongside another for SIB-decoding
	
	const char* regs[4][8] = {
		{ "ax", "cx", "dx", "bx", "sp", "bp", "si", "di" },
		{ "eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi" },
		{ "rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi" },
		{ "al", "cl", "dl", "bl", "sp", "bp", "sl", "dl" }
	};

	if (ins.expect_modrm) {
		u8 reg_mask = 0x38 + rex.r * 0x40;
		u8 reg = (*machine_data & (reg_mask << rex.b)) >> (3 + rex.b);

		u8 mod_mask = 0xC0 << (rex.b + rex.r);
		u8 mod = (*machine_data & mod_mask) >> (6 + rex.r + rex.b);

		u8 rm_mask = 0x07 | rex.b * 0x08;
		u8 rm = *machine_data & rm_mask;
		
		mem_set(ins_info -> byte_ins + str_len(ins_info -> byte_ins), ' ', sizeof(char));
		byte_str_into_hex_str(ins_info -> byte_ins + str_len(ins_info -> byte_ins), machine_data, 1);
		
		// Increase size as we've read the ModRM byte
		machine_data++;
		ins_size++;
		
		// TODO: The order and type of the operands should be better taken into consideration
		if (mod == 0x03) {
			int pos = str_len(ins_info -> ins_str);
			if (pos == MAX_DISASM_INS_LEN) return ins_size;
			mem_set(ins_info -> ins_str + pos, ' ', sizeof(char));
			str_cpy(ins_info -> ins_str + pos + 1, regs[operand_size][rm]);
		} else {
			DEBUG("mod: 0x%X, rm: 0x%X, reg: 0x%X", mod, rm, reg);
			u8 displacement_size = mod * mod;
			bool only_displacement = mod == 0 && rm == 0x05;
			
			int pos = str_len(ins_info -> ins_str);
			if (pos == MAX_DISASM_INS_LEN) return ins_size;
			str_cpy(ins_info -> ins_str + pos, " [");
			
			if (!only_displacement) str_cpy(ins_info -> ins_str + pos + 2, regs[2][rm]);
			else displacement_size = 4;

			if (rm == 0x04) TODO("implement SIB handling.");
			
			int displacement = 0;
			mem_cpy(&displacement, machine_data, displacement_size);
			if (displacement_size == 1) displacement = *((char*) &displacement);

			machine_data += displacement_size, ins_size += displacement_size;
			
			if (displacement != 0) {
				if (only_displacement && displacement < 0) mem_set(ins_info -> ins_str + str_len(ins_info -> ins_str), '-', sizeof(char));
				else if (displacement < 0) str_cpy(ins_info -> ins_str + str_len(ins_info -> ins_str), " - ");
				else str_cpy(ins_info -> ins_str + str_len(ins_info -> ins_str), " + ");
				
				displacement = ABS(displacement);
				
				byte_str_into_dec_val(ins_info -> ins_str + str_len(ins_info -> ins_str), (u8*) &displacement, displacement_size);
				mem_set(ins_info -> byte_ins + str_len(ins_info -> byte_ins), ' ', sizeof(char));
				byte_str_into_hex_str(ins_info -> byte_ins + str_len(ins_info -> byte_ins), machine_data - displacement_size, displacement_size);
			}

			mem_set(ins_info -> ins_str + str_len(ins_info -> ins_str), ']', sizeof(char));
		}

		OperandType second_operand = MIN(ins.second_operand + (ins.dynamic_operands_size * operand_effective_size_increment[operand_size]), ins.max_sec_operand_size);
		if (IS_IMM(second_operand)) {
			u8 imm_size = 1U << (second_operand - IMM_8);
			str_cpy(ins_info -> ins_str + str_len(ins_info -> ins_str), ", ");
			byte_str_into_hex_val(ins_info -> ins_str + str_len(ins_info -> ins_str), machine_data, imm_size);
			mem_set(ins_info -> byte_ins + str_len(ins_info -> byte_ins), ' ', sizeof(char));
			byte_str_into_hex_str(ins_info -> byte_ins + str_len(ins_info -> byte_ins), machine_data, imm_size);
			ins_size += imm_size;
		} else if ((IS_REG(second_operand) || IS_MEM(second_operand))) {	
			int pos = str_len(ins_info -> ins_str);
			if (pos == MAX_DISASM_INS_LEN) return ins_size;
			str_cpy(ins_info -> ins_str + pos, ", ");
			str_cpy(ins_info -> ins_str + pos + 2, regs[operand_size][reg]);
		}

	 } else if (ins.embedded_reg) {
		u8 reg = *(machine_data - 1) & 0x07;
		int pos = str_len(ins_info -> ins_str);
		if (pos == MAX_DISASM_INS_LEN) return ins_size;
		mem_set(ins_info -> ins_str + pos, ' ', sizeof(char));
		str_cpy(ins_info -> ins_str + pos + 1, regs[operand_size][reg]);
	 } 
	 
	if (!ins.expect_modrm && ins.first_operand != NONE) {
		OperandType first_operand = MIN(ins.first_operand + (ins.dynamic_operands_size * operand_effective_size_increment[operand_size]), ins.max_first_operand_size);
		if (IS_IMM(first_operand)) {
			u8 imm_size = 1U << (first_operand - IMM_8);
			mem_set(ins_info -> ins_str + str_len(ins_info -> ins_str), ' ', sizeof(char));
			byte_str_into_hex_val(ins_info -> ins_str + str_len(ins_info -> ins_str), machine_data, imm_size);
			mem_set(ins_info -> byte_ins + str_len(ins_info -> byte_ins), ' ', sizeof(char));
			byte_str_into_hex_str(ins_info -> byte_ins + str_len(ins_info -> byte_ins), machine_data, imm_size);
			ins_size += imm_size;
		} 	
	}
	
	if (!ins.expect_modrm && ins.second_operand != NONE) {
		OperandType second_operand = MIN(ins.second_operand + (ins.dynamic_operands_size * operand_effective_size_increment[operand_size]), ins.max_sec_operand_size);
		if (IS_IMM(second_operand)) {
			u8 imm_size = 1U << (second_operand - IMM_8);
			str_cpy(ins_info -> ins_str + str_len(ins_info -> ins_str), ", ");
			byte_str_into_hex_val(ins_info -> ins_str + str_len(ins_info -> ins_str), machine_data, imm_size);
			mem_set(ins_info -> byte_ins + str_len(ins_info -> byte_ins), ' ', sizeof(char));
			byte_str_into_hex_str(ins_info -> byte_ins + str_len(ins_info -> byte_ins), machine_data, imm_size);
			ins_size += imm_size;
		} 	
	 }

	return ins_size;
}

#endif //_WITC_H_

