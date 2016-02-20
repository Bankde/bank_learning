#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/user.h>

int main()
{   
    printf("This is Main Program.\nMy RealUID is: %d\nMy EffectiveUID is: %d\n", getuid(), geteuid());
    execl("getID.out", "getID.out", NULL);
    return 0;
}
