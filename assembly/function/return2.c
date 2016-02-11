#include <stdio.h>

int x(int i)
{
	printf("%d",i);
	return 0;
}

int main() {
	int a=x(3);
	printf("a=%d",a);
}

