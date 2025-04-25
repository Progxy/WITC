#include <stdio.h>
#include <stdlib.h>

#include "./utils.h"

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
static int decode_instruction(const u8* machine_data, const u64 size, InsInfo* ins_info) {
    printf("Opcode: 0x%02X\n", *machine_data);
    u8 opcode = *machine_data++;
    
    // Check if this opcode requires ModRM (simplified example, many do)
    if ((opcode >= 0x50 && opcode <= 0x5F) || (opcode >= 0xB8 && opcode <= 0xBF)) {
        printf("This opcode doesn't need a ModRM byte.\n");
        return -1;
    }

    u8 modrm = *machine_data++;
    u8 mod = (modrm & 0xC0) >> 6;
    u8 reg = (modrm & 0x38) >> 3;
    u8 rm  = (modrm & 0x07);

    printf("ModRM: 0x%02X (mod=%d, reg=%d, rm=%d)\n", modrm, mod, reg, rm);

    // Check if SIB is used
    if (mod != 3 && rm == 4) {
        u8 sib = *machine_data++;
        u8 scale = (sib & 0xC0) >> 6;
        u8 index = (sib & 0x38) >> 3;
        u8 base  = (sib & 0x07);

        printf("SIB: 0x%02X (scale=%d, index=%d, base=%d)\n", sib, scale, index, base);
    }

    // Displacement length depends on Mod value
    if (mod == 1) {
        int disp8 = *machine_data++;
        printf("Displacement (8-bit): %d\n", disp8);
    } else if (mod == 2) {
        int disp32 = *(u32*)machine_data;
        machine_data += 4;
        printf("Displacement (32-bit): %d\n", disp32);
    }

    // You could also check for immediates here if needed	
	
	return -1;
}

int main(void) {
	InsInfo ins_info = {0};

	int ret = decode_instruction(uefi_setup_data, uefi_setup_size, &ins_info);
	if (ret < 0) return ret;
	
	printf("Decode instruction %d bytes long.\n", ret);
	printf("(%s): %s.\n", ins_info.byte_ins, ins_info.ins_str);

	return 0;
}

