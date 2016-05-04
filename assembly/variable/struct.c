#include <stdio.h>
#include <stdlib.h>

// Struct stack structure is as followed:
// --- High memory address --- //
// --- return pointer && base stack --- //
// --- struct.three --- //
// --- struct.two --- //
// --- struct.one --- //
// --- ESP --- //

// Struct heap structure is as followed:
// --- High memory address --- //
// --- struct.three --- //
// --- struct.two --- //
// --- struct.one --- //
// --- Low memory address --- //


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
	struct struct_three* a = (struct struct_three*)malloc(sizeof(struct struct_three));
	a->one = 4;
	a->two = 5;
	a->three = 6;
	printf("One is %d\n", a->one);
	return 0;
}
