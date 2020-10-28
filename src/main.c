#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

int main(int argc, char* argv[])
{
    int i;
    FILE* file;
    char* output_hash;
    Hash_Algorithm* algorithm;

    if(argc != 3)
    {
        printf("Checksum <hash function> <filename>\n");
        return -1;
    }

    algorithm = NULL;
    for(i = 0; i < NB_HASH; i++)
    {
        if(!strcmp(argv[1], hash_algorithm[i].name))
        {
            algorithm = &hash_algorithm[i];
            break;
        }
    }

    if(!algorithm)
    {
        printf("Unknown hash function : %s\n", argv[1]);
        return -1;
    }

    file = fopen(argv[2], "r");
    if(!file)
    {
        perror("fopen");
        return -3;
    }

    output_hash = algorithm->handler(file);
    if(!output_hash)
		printf("Unable to hash the file using %s\n", algorithm->name);
	else
		printf("%s hash: %s\n", algorithm->name, output_hash);

    fclose(file);
    return 0;
}