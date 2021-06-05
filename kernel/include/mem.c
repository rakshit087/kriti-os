#include "mem.h"

//The function compares between two memory strings.
int memory_compare(int8* str1, int8* str2, uint32 len)
{
  const uint8* s1 = (const uint8*)str1;
  const uint8* s2 = (const uint8*)str2;
  while (len-- > 0)
  {
    if (*s1++ != *s2++)
    {
      return s1[-1] < s2[-1] ? -1 : 1;
    }
  }
  return 0;
}
//The function copies a memory string to another one.
void memory_copy(int8* src, int8* dest, int n)
{
  int8* csrc = (int8*)src;
  int8* cdest = (int8*)dest;

  for (int i = 0; i < n; i++)
  {
    cdest[i] = csrc[i];
  }
}
//The function sets any byte in a memory string with the same value.
void memory_set(void* dest, uint32 val, uint32 len)
{
  uint8 value = (uint8)(val & 0xFF);
  uint8* dest2 = (uint8*)(dest);

  int i = 0;

  while(i < len)
  {
    dest2[i] = value;
    i++;
  }
}

uint8 bcd2bin(uint8 bcd)
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}
