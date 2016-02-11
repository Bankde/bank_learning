#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	int i, count, minIndex;
	if (argc < 2 || argc > 4)
	{
		printf("Please input the system time.\n");
	}
	if (argc == 3)
	{
		minIndex = 0;
		count = atoi(argv[2]);
	}
	else if (argc == 4)
	{
		minIndex = atoi(argv[2]);
		count = atoi(argv[3]);
	}
	else
	{
		minIndex = 0;
		count = 10;
	}
	printf("Input is %d\n", atoi(argv[1]));
	srand(atoi(argv[1]));
	for (i = minIndex; i < minIndex + count; i++)
	{
		printf("%d: %d\n", (i+1), rand());
	}
	return 0;
}
