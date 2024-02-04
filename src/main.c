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

    if(argc < 2)
    {
        printf("Checksum <hash function> [file1 file2 ...]\n");
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

	for(i = 2; i < argc; i ++) {
		file = fopen(argv[i], "r");
		if(!file) {
			perror("fopen");
			return -3;
		}

		output_hash = algorithm->handler(file);
		if(!output_hash)
			printf("Unable to hash \"%s\" using %s\n", argv[i], algorithm->name);
		else {
			printf("%s  %s\n", output_hash, argv[i]);
			free(output_hash);
		}
    	
		fclose(file);
	}

	if(argc == 2) {
		file = stdin;
		output_hash = algorithm->handler(file);
		if(!output_hash)
			printf("Unable to hash stdin using %s\n", algorithm->name);
		else {
			printf("%s  stdin\n", output_hash);
			free(output_hash);
		}
	}

    return 0;
}