#ifndef _HASH_H_
#define _HASH_H_

#include <stdio.h>
#include <stdint.h>

typedef struct Hash_Algorithm Hash_Algorithm;
typedef char*(*Hash_Handler)(FILE*);

struct Hash_Algorithm
{
	char* name;
	Hash_Handler handler;
};

#define NEW_ALGORITHM(name) \
	{#name, name##_handler}

char* md5_handler(FILE* file);

static const Hash_Algorithm hash_algorithm[] = {
	NEW_ALGORITHM(md5),
};

#define NB_HASH sizeof(hash_algorithm) / sizeof(Hash_Algorithm)

#endif