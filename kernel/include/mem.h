#include "types.h"
int memory_compare(int8* str1, int8* str2, uint32 len);
void memory_copy(int8* src, int8* dest, int n);
void memory_set(void* dest, uint32 val, uint32 len);
uint8 bcd2bin(uint8 bcd);