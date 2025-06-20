#ifndef _COMMON_ISA_H_
#define _COMMON_ISA_H_

typedef enum OperandType { NONE = 0, DEFAULT_REG, REG_8, REG_16, REG_32, REG_64, MEM_8, MEM_16, MEM_32, MEM_64, REG_MEM_8, REG_MEM_16, REG_MEM_32, REG_MEM_64, IMM_8, IMM_16, IMM_32, IMM_64 } OperandType;

#define REG_MASK 0x38
#define MOD_MASK 0xC0
#define RM_MASK  0x07

#define IS_IMM(val)     ((val) >= IMM_8     && (val) <= IMM_64)
#define IS_REG(val)     ((val) >= REG_8     && (val) <= REG_64)
#define IS_MEM(val)     ((val) >= MEM_8     && (val) <= MEM_64)
#define IS_REG_MEM(val) ((val) >= REG_MEM_8 && (val) <= REG_MEM_64)
#define BIT_8_TYPE(val)                              \
	(IS_IMM(val) ? IMM_8 :                           \
		(IS_REG(val) ? REG_8 :                       \
			(IS_MEM(val) ? MEM_8 :                   \
				(IS_REG_MEM(val) ? REG_MEM_8 : NONE) \
			)                                        \
		)                                            \
	)

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
	char* default_reg;
	bool embedded_reg;
} Instruction;

#include "./amd_isa.h"

#endif //_COMMON_ISA_H_

