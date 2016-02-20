#include <stdio.h>

int main(int argc, char **argv)
{
	FILE *fp = NULL;
	char *s = "Secret is Hello World";

	if (argc > 1) {
		fp = fopen(argv[1], "w+");
		fputs(s, fp);
	}
	return 0;
}
