#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "util.h"

static const uint32_t md5_S[64] = {
	7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
	5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
	4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
	6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,
};

static const uint32_t md5_K[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

void md5_compute_digest(uint32_t *block, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d)
{
	int i;
	uint32_t F, g;
	uint32_t A, B, C, D;

	A = *a;
	B = *b;
	C = *c;
	D = *d;

	for(i = 0; i < 64; i ++) {
		if(i < 16) {
			F = (B & C) | (~B & D);
			g = i;
		} else if(i < 32) {
			F = (B & D) | (~D & C);
			g = (5*i + 1) % 16;
		} else if(i < 48) {
			F = B ^ C ^ D;
			g = (3*i + 5) % 16;
		} else {
			F = C ^ (B | ~D);
			g = (7*i) % 16;
		}

		F += A + md5_K[i] + block[g];
		A = D;
		D = C;
		C = B;
		B += rotate_left32(F, md5_S[i]);
	}

	*a += A;
	*b += B;
	*c += C;
	*d += D;
}

char* md5_handler(FILE* file)
{
	size_t length;
	size_t file_length;
	uint32_t a, b, c, d;
	uint8_t block[64];
	char* output;

	a = 0x67452301;
	b = 0xefcdab89;
	c = 0x98badcfe;
	d = 0x10325476;

	while((length = fread(block, 1, sizeof(block), file)) == sizeof(block))
		md5_compute_digest((uint32_t*) block, &a, &b, &c, &d);

	file_length = ftell(file);

	bzero(block + length, sizeof(block) - length);
	block[length] = 0x80;
	
	if(length >= 56) {
		md5_compute_digest((uint32_t*) block, &a, &b, &c, &d);
		bzero(block, sizeof(block));
	}

	file_length *= 8;
	
	((uint32_t*)block)[14] = (uint32_t) (file_length);
	((uint32_t*)block)[15] = (uint32_t) (file_length >> 32);

	md5_compute_digest((uint32_t*) block, &a, &b, &c, &d);

	output = (char*) malloc(sizeof(char) * 33);
	write_hex32_little_endian(output, a);
	write_hex32_little_endian(output + 8, b);
	write_hex32_little_endian(output + 16, c);
	write_hex32_little_endian(output + 24, d);
	output[32] = 0;
		
    return output;
}
