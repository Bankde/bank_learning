#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/user.h>
#include <sys/reg.h>

int main()
{   
    pid_t child;
    long orig_eax;
    int status;
    int i = 0;
    child = fork();
    if(child == 0) {
	printf("This is a child\n");
    }
    else {
	wait(0);
	printf("This is a parent\n");
    }
    return 0;
}
