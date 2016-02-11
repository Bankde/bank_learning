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
    char* childBuff = "Child\n";
    char* parentBuff = "Parent\n";
    child = fork();
    if(child == 0) {
	for (i = 0; i < 20; i++) {
	    write(1, childBuff, 6);
	}
    }
    else {
	for (i = 0; i < 20; i++) {
	    write(1, parentBuff, 7);
	} 
    }
    return 0;
}
