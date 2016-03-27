#include <stdio.h>
#include <stdlib.h>

struct struct_three{
	int one;
	int two;
	int three;
};

int main()
{
	struct struct_three s;
	s.one = 1;
	s.two = 2;
	s.three = 3;
	printf("One is %d\n", s.one);
	printf("Two is %d\n", s.two);
	printf("Three is %d\n", s.three);
	return 0;
}
