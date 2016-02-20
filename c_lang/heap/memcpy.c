#include <stdio.h>

int main(int argc, char* argv)
{
	char* a = (char *) malloc(20);
	char* b = (char *) malloc(25);
	a = "Hello World!\n";
	memcpy(b, a, 20);
	printf(b);
	return 0;
}
