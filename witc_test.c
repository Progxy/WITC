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
/// 	finit (= wait & fninit)
/// 	hlt
static const u8  uefi_setup_data[] = {0x9B, 0xDB, 0xE3, 0xF4};
static const u64 uefi_setup_size = 4;

// ---------------------------------------------------------------

int main(void) {
	u64 size = uefi_setup_size;
	u8* ptr = (u8*) uefi_setup_data;

	printf("\n");
	printf("\t╔══════════════════════════════════════════════════════════════════════╗\n");
	printf("\t║                      🕵️  WITC - What’s In The Code                    ║\n");
	printf("\t╠═════╤════════════╤════════════════════╤══════════════════════════════╣\n");
	printf("\t║ #   │ Address    │ Bytes              │ Instruction                  ║\n");
	
	for (u64 i = 0, j = 0; (long long int) size > 0; ++j) {
		printf("\t╟─────┼────────────┼────────────────────┼──────────────────────────────╢\n");
		
		InsInfo ins_info = {0};
		int ret = decode_instruction(ptr, size, &ins_info);
		
		printf("\t║ %03llu │ 0x%08llX │ %-18s │ %-28s ║\n", j, i, ins_info.byte_ins, ins_info.ins_str);
		
		size -= ret, ptr += ret, i += ret;
	}

	printf("\t╚═════╧════════════╧════════════════════╧══════════════════════════════╝\n");
	printf("\n");

	return 0;
}

