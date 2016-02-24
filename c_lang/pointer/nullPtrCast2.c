#include <stdio.h>

// Casting from nullptr -> charptr
// Very possible

int func1(void *argv)
{
	char* c = (char*)argv;
	printf("Sub -- %s\n", c);
	return 0;
}

int main(int argc, char** argv)
{
	char* c = "ABCD";
	func1(c);
	return 0;	
}
