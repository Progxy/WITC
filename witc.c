#include <stdio.h>
#include <stdlib.h>

#include "./utils.h"

static const u8 uefi_timer_data[] = {0xFA, 0x48, 0xCF};
static const u64 uefi_timer_size = 3;
static const u8 uefi_setup_data[] = {0x9B, 0xDB, 0xE3, 0xF4};
static const u64 uefi_setup_size = 4;

static int decode_instruction(u64 rip, InsInfo* ins_info) {
	printf("Decoding instruction at 0x%llX", rip);
	return -1;
}

int main(void) {
	printf("Hello World.\n");
	return 0;
}
