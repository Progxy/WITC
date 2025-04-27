#ifndef _WITC_H_
#define _WITC_H_

#include "./utils.h"

static const u64 opcodes[] = { 0x9B, 0xDBE3, 0x9BDBE3, 0xF4, 0xFA, 0xCF, 0xF16444 };
static const char* opcodes_mnemonics[] = { "wait", "fninit", "finit", "hlt", "cli", "iret", "unknown/illegal instruction" };
static const bool opcodes_mnemonics_ins[] = { 0,      0,        0,      0,     0,      1,      0 };

// ---------------------------------------------------------------
static inline int simple_ins_match(const u64 opcode) {
	for (u64 i = 0; i < ARR_SIZE(opcodes); ++i) {
		if (opcode == opcodes[i]) return i;
	}
	return -1;
}

static u8 decode_instruction(const u8* machine_data, const u64 size, InsInfo* ins_info) {
	int ret = 0;
	u64 opcode = *machine_data++;

	// Instruction defaults to 32-bits, so this suffix is always present
	char suffix = 'd';
	if (opcode >= 0x40 && opcode <= 0x4F) {
		suffix = 'q';
		if (size <= 1) ret = -1;
		else opcode = *machine_data++;
	} else if (opcode == 0x66) {
		suffix = '\0';
		if (size <= 1) ret = -1;
		else opcode = *machine_data++;
	}
	
	if (suffix != 'd') {
		byte_str_into_hex_str(ins_info -> byte_ins, machine_data - (1 + (ret != -1)), 1);
		mem_set(ins_info -> byte_ins + 2, ' ', sizeof(char));
	}

	u8 ins_size = 1;
	if (ret == 0) ret = simple_ins_match(opcode);
	
	for (; ins_size < size - (suffix != 'd') && ret < 0; ++ins_size) {
		opcode = (opcode << 8) | *machine_data++;
		ret = simple_ins_match(opcode);
	}
	
	if (ret == -1) ret = ARR_SIZE(opcodes_mnemonics) - 1;
	
	byte_str_into_hex_str(ins_info -> byte_ins + (suffix != 'd') * 3, (u8*) &opcode, ins_size);
	str_cpy(ins_info -> ins_str, opcodes_mnemonics[ret]);
	if (suffix != '\0' && opcodes_mnemonics_ins[ret]) mem_set(ins_info -> ins_str + str_len(ins_info -> ins_str), suffix, sizeof(char));
	ins_size += suffix != 'd';

	return ins_size;
}

#endif //_WITC_H_

