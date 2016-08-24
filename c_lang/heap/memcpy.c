#include <stdio.h>

int main(int argc, char** argv)
{
	char* a = (char *) malloc(20);
	char* b = (char *) malloc(25);
	memcpy(a, "Hello World!\n", 13);
	memcpy(b, a, 20);
	printf(b);
	free(a);
	free(b);
	return 0;
}
