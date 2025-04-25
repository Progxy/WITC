#ifndef _UTILS_H_
#define _UTILS_H_

#define STATIC_ASSERT          _Static_assert

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;
STATIC_ASSERT(sizeof(u8)   == 1,  "u8 must be 1 byte");
STATIC_ASSERT(sizeof(u16)  == 2,  "u16 must be 2 bytes");
STATIC_ASSERT(sizeof(u32)  == 4,  "u32 must be 4 bytes");
STATIC_ASSERT(sizeof(u64)  == 8,  "u64 must be 8 bytes");
 
typedef unsigned char bool;

#define MAX_DISASM_INS_LEN 129
#define MAX_BYTE_REPR_LEN  33
typedef struct InsInfo {
	char ins_str[MAX_DISASM_INS_LEN];
	char byte_ins[MAX_BYTE_REPR_LEN];
} InsInfo;

#endif //_UTILS_H_
