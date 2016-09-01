#include <stdio.h>

int main(int argc, char** argv) {
#if __CYGWIN__
	printf("Cygwin\n");
#endif
#if __FREEBSD__
	printf("FreeBSD\n");
#endif
#if __linux__ // Linux kernel
	printf("Linux Kernel\n");
#endif
#if macintosh // Mac OS 9
	printf("Mac OS 9\n");
#endif
#if __APPLE__ && __MACH__ // Mac OS X
	printf("Mac OS X\n");
#endif
#if __MSDOS__
	printf("MSDOS\n");
#endif
#if __unix__
	printf("Unix Environment\n");
#endif
#if __WINDOWs__
	printf("Windows\n");
#endif
#if _WIN32
	printf("Winx32\n");
#endif
#if _WIN64
	printf("Winx64\n");
#endif
}
