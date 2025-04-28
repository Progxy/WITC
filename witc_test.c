#include <stdio.h>
#include <stdlib.h>

/* #define _ENABLE_DEBUG_ */

#define _SUPPORT_FUNCTIONS_
#define _SPECIAL_TYPE_SUPPORT_
#include "./witc.h"

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Usage: witc_test <input-binary>\n");
		return 69;
	}
	
	u64 size = 0;
	u8* ptr = NULL;
	const char* bin_path = argv[1];
	if (read_bin(bin_path, &size, &ptr) < 0) {
		printf("An error occurred while reading the binary file: '%s'\n", bin_path);
		return 69;
	}

	bin_dump(ptr, size);

	printf("\n");
	printf("\t╔════════════════════════════════════════════════════════════════════════════╗\n");
	printf("\t║                      🕵️  WITC - What’s In The Code                          ║\n");
	printf("\t╠═════╤════════════╤══════════════════════════╤══════════════════════════════╣\n");
	printf("\t║ #   │ Address    │ Bytes                    │ Instruction                  ║\n");
	
	void* orig_ptr = ptr;
	for (u64 i = 0, j = 0; (long long int) size > 0; ++j) {
		printf("\t╟─────┼────────────┼──────────────────────────┼──────────────────────────────╢\n");
		
		InsInfo ins_info = {0};
		int ret = decode_instruction(ptr, size, &ins_info);
		if (ret < 0) {
			printf("\t║ %03llu │ 0x%08llX │ %-24s │ %-28s ║\n", j, i, ins_info.byte_ins, "unknown/illegal instruction");
			break;
		}	

		printf("\t║ %03llu │ 0x%08llX │ %-24s │ %-28s ║\n", j, i, ins_info.byte_ins, ins_info.ins_str);
		
		size -= ret, ptr += ret, i += ret;
	}

	printf("\t╚═════╧════════════╧══════════════════════════╧══════════════════════════════╝\n");
	printf("\n");

	free(orig_ptr);

	return 0;
}

