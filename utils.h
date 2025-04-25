#ifndef _UTILS_H_
#define _UTILS_H_

#define ARR_SIZE(arr) (sizeof(arr) / sizeof(*(arr)))

#ifdef _SPECIAL_TYPE_SUPPORT_
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

#endif //_SPECIAL_TYPE_SUPPORT_

#define MAX_DISASM_INS_LEN 129
#define MAX_BYTE_REPR_LEN  33
typedef struct InsInfo {
	char ins_str[MAX_DISASM_INS_LEN];
	char byte_ins[MAX_BYTE_REPR_LEN];
} InsInfo;

#ifdef _SUPPORT_FUNCTIONS_

#define MAX(a, b) ((a) >= (b) ? (a) : (b)) 
#define MIN(a, b) ((a) <= (b) ? (a) : (b)) 

#define CAST_PTR(ptr, type) ((type*) (ptr))

static size_t str_len(const char* str) {
    if (str == NULL) return 0;
	size_t i = 0;
    while (*str++) ++i;
    return i;
}

static void* mem_cpy(void* dest, const void* src, size_t size) {
	if (dest == NULL || src == NULL) return NULL;
	for (size_t i = 0; i < size; ++i) CAST_PTR(dest, unsigned char)[i] = CAST_PTR(src, unsigned char)[i];
	return dest;
}

static char* str_cpy(char* dest, const char* restrict src) {
	if (dest == NULL || src == NULL) return NULL;
	mem_cpy((void*) dest, (void*) src, str_len(src) + 1);
	return (char*) dest;
}

static const char hex_chrs[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

static void byte_str_into_hex_str(char* str, u8* byte_str, u8 byte_size) {
	for (u8 i = 0, j = 0; i < byte_size; ++i, ++j) {
		str[j++] = hex_chrs[(byte_str[i] >> 4) & 0xF];
		str[j] = hex_chrs[byte_str[i] & 0xF];
		if (i < byte_size - 1) str[++j] = ' ';
	}
	return;
}

#endif //_SUPPORT_FUNCTIONS_

#endif //_UTILS_H_
