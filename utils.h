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

#endif //_SUPPORT_FUNCTIONS_

#endif //_UTILS_H_
