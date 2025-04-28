#ifndef _UTILS_H_
#define _UTILS_H_

#define ARR_SIZE(arr) (sizeof(arr) / sizeof(*(arr)))
#define PACKED_STRUCT __attribute__((packed))
#define UNUSED_FUNCTION __attribute__((unused))

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

#define TRUE  1
#define FALSE 0

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

#ifdef _ENABLE_DEBUG_
	#define DEBUG(fmt, ...)  printf("\033[38;5;214m[" __FILE__ "::%u]\033[35m DEBUG: \033[0m" fmt "\n", __LINE__, ##__VA_ARGS__)
#else
	#define DEBUG(fmt, ...)
#endif //_ENABLE_DEBUG_

static size_t str_len(const char* str) {
    if (str == NULL) return 0;
	size_t i = 0;
    while (*str++) ++i;
    return i;
}

#define mem_set(ptr, value, size)    mem_set_var(ptr, value, size, sizeof(u8))
#define mem_set_32(ptr, value, size) mem_set_var(ptr, value, size, sizeof(u32))
#define mem_set_64(ptr, value, size) mem_set_var(ptr, value, size, sizeof(u64))
static void mem_set_var(void* ptr, int value, size_t size, size_t val_size) {
	if (ptr == NULL) return;
	for (size_t i = 0; i < size; ++i) CAST_PTR(ptr, unsigned char)[i] = CAST_PTR(&value, unsigned char)[i % val_size]; 
	return;
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

UNUSED_FUNCTION static int str_tok(const char* str, const char* delim) {
     for (u64 i = 0, j = 0; i <= str_len(str); ++i) {
         if (delim[j] == str[i]) {
            if ((j + 1) == str_len(delim)) return i - j;
            j++;
         } else if (j > 0) i -= j, j = 0;
    }
    return -1;
}

static const char hex_chrs[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

static void byte_str_into_hex_str(char* str, const u8* byte_str, u8 byte_size) {
	for (u8 i = 0, j = 0; i < byte_size; ++i, ++j) {
		str[j++] = hex_chrs[(byte_str[i] >> 4) & 0xF];
		str[j] = hex_chrs[byte_str[i] & 0xF];
		if (i < byte_size - 1) str[++j] = ' ';
	}
	return;
}

static void byte_str_into_hex_val(char* str, const u8* byte_str, u8 byte_size) {
	str[0] = '0', str[1] = 'x', str += 2;
	for (u8 i = byte_size, j = 0; i > 0; --i, ++j) {
		str[j++] = hex_chrs[(byte_str[i - 1] >> 4) & 0xF];
		str[j] = hex_chrs[byte_str[i - 1] & 0xF];
	}
	return;
}

#endif //_SUPPORT_FUNCTIONS_

static int read_bin(const char* bin_path, u64* bin_size, u8** bin_data) {
	FILE* bin_file = NULL;
	if ((bin_file = fopen(bin_path, "rb")) == NULL) {
		perror("Failed to read the binary file");
		return -1;
	}

	if (fseek(bin_file, 0, SEEK_END) < 0) {
		perror("Failed to seek to the end of the binary file");
		return -1;
	}
	
	*bin_size = ftell(bin_file);
	if ((long int) *bin_size < 0) {
		perror("Failed to read the binary file size");
		return -1;
	}
	
	if (fseek(bin_file, 0, SEEK_SET) < 0) {
		perror("Failed to seek to the start of the binary file");
		return -1;
	}

	if ((*bin_data = calloc(*bin_size, sizeof(u8))) == NULL) {
		perror("Failed to allocate the binary data buffer");
		fclose(bin_file);
		return -1;
	}
	
	size_t ret = 0;
	if ((ret = fread(*bin_data, sizeof(u8), *bin_size, bin_file)) != (size_t) *bin_size) {
		perror("Failed to read the content of the bin file");
		free(*bin_data);
		return -1;
	}

	fclose(bin_file);

	return 0;
}

#endif //_UTILS_H_
