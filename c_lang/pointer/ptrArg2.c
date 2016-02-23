#include <stdio.h>

int func1(int* argv)
{
	*argv = 5;
	printf("Sub -- %d\n", *argv);
	return 0;
}

int main(int argc, char** argv)
{
	int i = 10;
	printf("Main before -- %d\n", i);
	func1(&i);
	printf("Main after -- %d\n", i);
	return 0;	
}
