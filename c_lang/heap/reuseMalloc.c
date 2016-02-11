#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int a = (int*)malloc(400);
	int b;
	strcpy(a, "Test me");
	printf("%x say: %s\n", a, (char*)a);
	free(a);
	b = (int*)malloc(400);
	printf("%x got: %s\n", b, (char*)b);
	free(b);
	return 0;
}
