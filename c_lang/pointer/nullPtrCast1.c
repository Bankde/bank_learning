#include <stdio.h>

// Casting from nullptr -> int
// Casting is possible (nullptr is 8 bytes while int is 4 bytes)

int func1(void *argv)
{
	int i = (int)argv;
	printf("Sub -- %d\n", i);
	return 0;
}

int main(int argc, char** argv)
{
	int i = 10;
	func1(i);
	return 0;	
}
