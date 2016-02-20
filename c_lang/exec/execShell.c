#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{   
	execl("/bin/bash", "This is a Bash", NULL);
    return 0;
}
