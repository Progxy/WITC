#ifndef _WITC_UTILS_H_
#define _WITC_UTILS_H_

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

#define ABS(a)    ((a) < 0 ? -(a) : (a))
#define CLAMP(val, min, max) ((val) > (max) ? (max) : ((val) < (min) ? (min) : (val)))

#ifdef _SUPPORT_FUNCTIONS_
#define ARR_SIZE(arr) (sizeof(arr) / sizeof(*(arr)))
#define PACKED_STRUCT __attribute__((packed))
#define UNUSED_FUNCTION __attribute__((unused))

#define TODO(msg)           \
	do {					\
		printf(msg "\n");   \
		abort();            \
	} while(FALSE)            

#define CAST_PTR(ptr, type) ((type*) (ptr))
#define MAX(a, b) ((a) >= (b) ? (a) : (b)) 
#define MIN(a, b) ((a) <= (b) ? (a) : (b)) 

#ifdef _ENABLE_DEBUG_
	#define DEBUG(fmt, ...)  printf("\033[38;5;214m[" __FILE__ "::%u]\033[35m DEBUG: \033[0m" fmt "\n", __LINE__, ##__VA_ARGS__)
#else
	#define DEBUG(fmt, ...)
#endif //_ENABLE_DEBUG_

static size_t str_len(const char* str) {
    if (str == NULL) return 0;
    const char* str_c = str;
	while (*str++);
    return (size_t) (str - str_c - 1);
}

#define mem_set(ptr, value, size)    mem_set_var(ptr, value, size, sizeof(u8))
#define mem_set_32(ptr, value, size) mem_set_var(ptr, value, size, sizeof(u32))
#define mem_set_64(ptr, value, size) mem_set_var(ptr, value, size, sizeof(u64))
static void mem_set_var(void* ptr, long long int value, size_t size, size_t val_size) {
	if (ptr == NULL) return;
	u8* p = (u8*) ptr;
	const size_t s = size;
	while (size--) *p++ = CAST_PTR(&value, unsigned char)[(s - size) % val_size]; 
	return;
}

static void* mem_cpy(void* dest, const void* src, size_t size) {
	if (dest == NULL || src == NULL) return NULL;
	u8* dp = (u8*) dest;
	u8* sp = (u8*) src;
	while (size--) *dp++ = *sp++;
	return dest;
}

static void* mem_move(void* dest, const void* src, size_t size) {
    if (dest == NULL || src == NULL || size == 0) return NULL;
    
	size_t s = size;
	u8* temp = (u8*) calloc(size, sizeof(u8));
	if (temp == NULL) {
		printf("Failed to allocate the temp buffer for mem_move.\n");
		return NULL;
	}
	
	u8* dp = CAST_PTR(dest, u8);
	u8* sp = (u8*) src;

	while (size--) *temp++ = *sp++;
	temp -= s, size = s;
	while (s--)	*dp++ = *temp++;
	
	free(temp - size);
    
    return dest;
}

static char* str_cpy(char* dest, const char* restrict src) {
	if (dest == NULL || src == NULL) return NULL;
	char* o_dest = dest;
  	while ((*dest++ = *src++));
	return o_dest;
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

static void bin_dump(u8* bin_data, u64 size) {
    printf("\t╔══════════════════════════════════════════════════════════════╗\n");
    printf("\t║                 Bin Dump (%llu bytes)                        ║\n", size);
    printf("\t╠══════════════════════════════════════════════════════════════╣\n");
    
    for (u64 i = 0; i < size; ++i) {
        if (i % 16 == 0) printf("\t║  0x%04llX: ", i);
        
        printf("%02X ", bin_data[i]);
        
        if ((i + 1) % 16 == 0 || i == size - 1) printf(" %*.s║\n", (int) (i == size - 1 ? 3 * (16 - ((i + 1) % 16) + 1) : 3), " ");
    }
    
	printf("\t╚══════════════════════════════════════════════════════════════╝\n\n");
    
	return;
}

#endif //_SUPPORT_FUNCTIONS_

#ifdef _BASE_SUPPORT_FUNCTIONS_
#define set_char(ptr, chr) mem_set((ptr), chr, sizeof(char))

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

static void byte_str_into_dec_val(char* str, const u8* byte_str, u8 byte_size) {
	u64 val = 0;
	for (u8 i = byte_size; i > 0; --i) {
		val *= 256;
		val += byte_str[i - 1];
	}
	
	char* const str_base = str;
	while (val) {
		mem_move(str_base + 1, str_base, str - str_base);
		u8 value = val % 10;
		*str_base = value + '0', str++;
		val = (val - (val % 10)) / 10;
	}
	
	return;
}

#endif //_BASE_SUPPORT_FUNCTIONS_

#endif //_WITC_UTILS_H_
