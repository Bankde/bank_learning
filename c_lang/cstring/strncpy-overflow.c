#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
        char a[16] = "abcdefghijklmno";
        char b[16] = "1234";
        char c[16] = "abcdefghijklmno";
        // strncpy 16 will make this program overflow (15 should be max with 1 null terminator added)
        strncpy(b, "1234567890123456789012345", 16);
	printf("%s", b);
}
