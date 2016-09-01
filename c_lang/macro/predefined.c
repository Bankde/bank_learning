#include <stdio.h>

// Information: https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html

int main(int argc, char** argv) {
	printf("These are standard predefined macros.\n");
	printf("File: %s\n", __FILE__);
	printf("Line: %d\n", __LINE__);
	printf("Func: %s\n", __FUNCTION__);
	printf("Date: %s\n", __DATE__);
	printf("Time: %s\n", __TIME__);
	printf("isStandardC: %d\n", __STDC__);
#if __STDC_VERSION__ // This macro is available when compile using gcc
	printf("STDC_version: %ld\n", __STDC_VERSION__);
#endif
	printf("isHosted: %d\n", __STDC_HOSTED__);
#if __cplusplus // This macro is available when compile using g++
	printf("isCPP: %ld\n", __cplusplus);
#endif
#if __OBJC__
	printf("isOBJC: %d\n", __OBJC__);
#endif
#if __ASSEMBLER__
	printf("isASM: %d\n", __ASSEMBLER__);
#endif
}
