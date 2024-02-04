#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdint.h>

uint32_t rotate_left32(uint32_t val, int shift);
void write_hex8(char* out, uint8_t val);
void write_hex32_little_endian(char* out, uint32_t val);

#endif
