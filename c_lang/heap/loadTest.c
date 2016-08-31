#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	int index = 1;
	int maxRun = 1000000;
	int memSize = 1000;
	char mode = 0;
	while (index < argc) {
		if (strcmp(argv[index],"-n") == 0) {
			index++;
			maxRun = atoi(argv[index]);
			index++;
		}
		else if (strcmp(argv[index],"-s") == 0) {
			index++;
			memSize = atoi(argv[index]);
			index++;
		}
		else if (strcmp(argv[index],"-m") == 0) {
			index++;
			if (strcmp(argv[index],"malloc") == 0)
				mode = 0;
			else if (strcmp(argv[index],"calloc") == 0)
				mode = 1;
			else {
				printf("Wrong mode detected: default to malloc\n");
				mode = 0;
			}	
			index++;
		}
		else {
			printf("=== This is a help mode on malloc/calloc loadtest ===\n");
			printf("This program loops a malloc/calloc followed by free\n");
			printf("To use: time ./loadTest.out [argument here]\n");
			printf("-n [number here] for number of run (default is 1000000)\n");
			printf("-s [number here] for size of memory to allocate\n");
			printf("-m [malloc/calloc] choose either malloc or calloc to run\n");
			printf("=== The end ===\n");
			return 0;
		}
	}
	if (mode == 0) {
		for (int i = 0; i < maxRun; i++) {
			char* test = (char*)malloc(memSize);
			free(test);
		}
	}
	else if (mode == 1) {
		for (int i = 0; i < maxRun; i++) {
			char* test = (char*)calloc(memSize,1);
			free(test);
		}
	}
	return 0;
}
