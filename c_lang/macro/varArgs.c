#include <stdio.h>

#define debug(format, ...) fprintf (stderr, format, __VA_ARGS__)

int main(int argc, char** argv) {
	// debug("Hello\n"); // This is not allowed (You cannot leave variable argument out completely //
	debug("This is one: %d\n", 1);
	debug("Multi: %d, %s, %d and %c\n", 10, "Test", 1337, 'A');
	return 0;
}
