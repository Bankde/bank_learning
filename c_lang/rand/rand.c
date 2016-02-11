#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int seed;
	int i = 0;

	if (argc < 2)
		seed = 0;
	else
		seed = atoi(argv[1]);

	srand(seed);
	printf("Seed is %d\n", seed);
	for (i = 0; i < 60; i++)
	{
		printf("Rand%d is %d\n", i, rand());
	}
	return 0;
}
