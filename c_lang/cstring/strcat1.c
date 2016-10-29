#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int bufferLen = 30;
	char injectCode[50];
	int i = 0;
	strcpy(injectCode, "Sample Sentence");
        // fill bufferLen with garbage
	for (i = strlen(injectCode); i < bufferLen; i++) injectCode[i] = 'a';
        // overflow with address
	injectCode[bufferLen] = 'A';
	injectCode[bufferLen+1] = 'B';
	injectCode[bufferLen+2] = 'C';
	injectCode[bufferLen+3] = 'D';
	injectCode[bufferLen+4] = 'E';
        // end the overflow
	injectCode[bufferLen+5] = '\x00';
	printf("%s", injectCode);
}

