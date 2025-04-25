#ifndef _WITC_H_
#define _WITC_H_

#include "./utils.h"

static const u64 opcodes[] = { 0x9B, 0xDBE3, 0x9BDBE3 };
static const u8 opcodes_lens[] = { 1, 2, 3 };
static const char* opcodes_mnemonics[] = { "wait", "fninit", "finit" };
static const char hex_chrs[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

static inline int simple_ins_match(const u64 opcode) {
	for (u64 i = 0; i < ARR_SIZE(opcodes); ++i) {
		if (opcode == opcodes[i]) return i;
	}
	return -1;
}

static void byte_str_into_hex_str(char* str, u8* byte_str, u8 byte_size) {
	for (u8 i = 0, j = 0; i < byte_size; ++i, ++j) {
		str[j++] = hex_chrs[(byte_str[i] >> 4) & 0xF];
		str[j] = hex_chrs[byte_str[i] & 0xF];
		if (i < byte_size - 1) str[++j] = ' ';
	}
	return;
}

static int decode_instruction(const u8* machine_data, const u64 size, InsInfo* ins_info) {
	int ret = -1;
    u64 index = 1;
    u64 opcode = *machine_data++;

	while (index < size) {
		ret = simple_ins_match(opcode);
		if (ret >= 0) {
			byte_str_into_hex_str(ins_info -> byte_ins, (u8*) &opcode, opcodes_lens[ret]);
			str_cpy(ins_info -> ins_str, opcodes_mnemonics[ret]);
			ret = opcodes_lens[ret];
			break;
		}
		opcode = (opcode << 8) | *machine_data++;
		index++;
	}
	
	return ret;
}

#endif //_WITC_H_

