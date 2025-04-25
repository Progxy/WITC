#include <stdio.h>
#include <stdlib.h>

#define _SUPPORT_FUNCTIONS_
#define _SPECIAL_TYPE_SUPPORT_
#include "./witc.h"

// -------------------
//  Test Machine Code
// -------------------
/// Disassembled:
/// 	cli
/// 	iretq
static const u8  uefi_timer_data[] = {0xFA, 0x48, 0xCF};
static const u64 uefi_timer_size = 3;

/// Disassembled:
/// 	finit
/// 	hlt
static const u8  uefi_setup_data[] = {0x9B, 0xDB, 0xE3, 0xF4};
static const u64 uefi_setup_size = 4;

// ---------------------------------------------------------------

int main(void) {
	InsInfo ins_info = {0};
	u64 size = uefi_setup_size;
	u8* ptr = (u8*) uefi_setup_data;
		
	while (size) {
		int ret = decode_instruction(ptr, size, &ins_info);
		if (ret <= 0) return ret;
		size -= ret, ptr += ret;
		printf(" --> (%s): %s.\n", ins_info.byte_ins, ins_info.ins_str);
	}

	return 0;
}

