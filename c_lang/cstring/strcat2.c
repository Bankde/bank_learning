#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int overflow = 30;
	char buf2[50];
	int i = 0;
	strcpy(buf2,"This is a test");
	for (i = 14; i < overflow; i++) buf2[i] = 'a';
	buf2[overflow] = 'A';
	buf2[overflow+1] = 'B';
	buf2[overflow+2] = 'C';
	buf2[overflow+3] = 'D';
	buf2[overflow+4] = 'E';
	buf2[overflow+5] = '\x00';
	printf("%s", buf2);
}
