#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/user.h>

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
	wait(NULL);
	printf("This is Parent.\nMy RealUID is: %d\nMy EffectiveUID is: %d\n", getuid(), geteuid());
//	execl("/usr/bin/whoami", "/usr/bin/whoami", NULL);
	execl("/home/bankde/Desktop/Learning/fork/getID", "/home/bankde/Desktop/Learning/fork/getID", NULL);
    }
    else {
	printf("This is Child.\nMy RealUID is: %d\nMy EffectiveUID is: %d\n", getuid(), geteuid());
//	execl("/usr/bin/whoami", "/usr/bin/whoami", NULL);
	execl("/home/bankde/Desktop/Learning/fork/getID", "/home/bankde/Desktop/Learning/fork/getID", NULL);
    }
    return 0;
}
