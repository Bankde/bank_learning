#include <stdio.h>
#include <stdlib.h>

// In this try, we try to study behavior of strcpy and the result is:
// 1. strcpy will copy the string to the specified location (replace what is already there)
// 2. after copying, strcpy will automatically add null to the end

int main()
{
	char* a = (char*)malloc(10*sizeof(char));
	memcpy(a, "aaaaaaaaaa", 10);
	a[2] = '\0';
	strcpy(a, "Test");
	printf("%s", a);
	return 0;
}
