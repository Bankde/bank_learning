#include <stdio.h>
#include <stdlib.h>

// In this try, we try to study behavior of strcat and the result is:
// 1. strcat seeks for first null
// 2. it concatenates the string replacing that null it found
// 3. strcat will automatically add null at the end

int main()
{
	char* a = (char*)malloc(10*sizeof(char));
	memcpy(a, "aaaaaaaaaa", 10);
	a[2] = '\0';
	strcat(a, "Test");
	printf("%s", a);
	return 0;
}
