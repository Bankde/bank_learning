#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// http://stackoverflow.com/questions/14916678/why-does-free-only-set-the-8-first-bytes-to-zero

int main()
{
	int a = (int*)malloc(10);
	int b;
	strcpy(a, "Test me");
	printf("%x say: %s\n", a, (char*)a);
	free(a);
	b = (int*)malloc(10);
	printf("%x got: %s\n", b, (char*)b);
	free(b);
	return 0;
}
