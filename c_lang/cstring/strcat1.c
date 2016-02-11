#include <stdlib.h>
#include <stdio.h>

char code[] = "This is a test";

int main(int argc, char **argv)
{
	int overflow = 30;
	char buf[strlen(code)];
	char buf2[50];
	int i = 0;
	strcpy(buf,code);
	strcpy(buf2,buf);
	for (i = strlen(code); i < overflow; i++) buf2[i] = 'a';
	buf2[overflow] = 'A';
	buf2[overflow+1] = 'B';
	buf2[overflow+2] = 'C';
	buf2[overflow+3] = 'D';
	buf2[overflow+4] = 'E';
	buf2[overflow+5] = '\x00';
	printf("%s", buf2);
}

