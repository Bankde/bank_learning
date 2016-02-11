#include <stdio.h>

int main(int argc, char **argv)
{
	FILE *fp = NULL;
	char buffer[4096];

	if (argc > 1) {
		fp = fopen(argv[1], "r");
		fread(buffer, 1, 4096, fp);
		printf("%s\n", buffer);
	}
	return 0;
}
