#include <stdio.h>

// Casting from nullptr -> char
// Since nullptr can't do arithmatic, we have to cast to char* first
// then (i will add better explanination later) need to do work now 

int func1(void *argv)
{
	char* in = (char*)argv;
	char c[10];
	c[0] = *in;
	c[1] = *(in+1);
	c[2] = *(in+2);
	c[3] = *(in+3);
	c[4] = '\x00';
	printf("Sub -- %s\n", c);
	return 0;
}

int main(int argc, char** argv)
{
	char* c;
	c = "ABCD";
	func1(c);
	return 0;	
}
