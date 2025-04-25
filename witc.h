#ifndef _WITC_H_
#define _WITC_H_

#include "./utils.h"

static const u64 opcodes[] = { 0x9B, 0xDBE3, 0x9BDBE3, 0xF4, 0xFA, 0xCF, 0xF16444 };
static const u8 opcodes_lens[] = { 1, 2, 3, 1, 1, 1, 8 };
static const char* opcodes_mnemonics[] = { "wait", "fninit", "finit", "hlt", "cli", "iretq", "unknown/illegal instruction" };

// ---------------------------------------------------------------
static inline int simple_ins_match(const u64 opcode) {
	for (u64 i = 0; i < ARR_SIZE(opcodes); ++i) {
		if (opcode == opcodes[i]) return i;
	}
	return -1;
}

static u8 decode_instruction(const u8* machine_data, const u64 size, InsInfo* ins_info) {
    u64 opcode = *machine_data++;
	int ret = simple_ins_match(opcode);

	for (u64 i = 1; i < size && ret < 0; ++i) {
		opcode = (opcode << 8) | *machine_data++;
		ret = simple_ins_match(opcode);
	}
	
	if (ret == -1) ret = ARR_SIZE(opcodes_mnemonics) - 1;
	
	byte_str_into_hex_str(ins_info -> byte_ins, (u8*) &opcode, MIN(opcodes_lens[ret], size));
	str_cpy(ins_info -> ins_str, opcodes_mnemonics[ret]);

	return MIN(opcodes_lens[ret], size);
}

#endif //_WITC_H_

