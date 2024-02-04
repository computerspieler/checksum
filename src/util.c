#include <stdint.h>

#include "util.h"

uint32_t rotate_left32(uint32_t val, int shift)
{
	return (val << shift) | (val >> (32 - shift));
}

void write_hex8(char* out, uint8_t val)
{
	int hi, lo;
	
	hi = (val >> 4) & 0xF;
	lo = val & 0xF;

	out[0] = hi >= 10 ? (hi - 10 + 'a') : (hi + '0');
	out[1] = lo >= 10 ? (lo - 10 + 'a') : (lo + '0');
}

void write_hex32_little_endian(char* out, uint32_t val)
{
	int i;
	for(i = 0; i < 4; i ++)
		write_hex8(out + 2*i, (val >> (8 * i)) & 0xFF);
}