#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/reg.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

// The result looks like the threadID will accumulate among every process
// The result is as followed:
// 25567248 -- PID: 28536		ThreadID: 28537
// 25567248 -- PID: 28536		ThreadID: 28539
// 25567248 -- PID: 28536		ThreadID: 28538
// parent started
// 25567248 -- PID: 28535		ThreadID: 28540
// 25567248 -- PID: 28535		ThreadID: 28541
// 25567248 -- PID: 28535		ThreadID: 28542

void *threadFunc(void *arg)
{
	int num = *(int*)arg;
	pid_t tid = syscall(SYS_gettid);
	pid_t pid = getpid();
	printf("%d -- PID: %d\t\tThreadID: %d\n", num, pid, tid);
}

int main(int argc, char** argv)
{   
    pid_t child;
    int i = 0;
    int *j = (int*)malloc(sizeof(int));

    child = fork();
    if(child == -1)
	printf("fork fail\n");
    if(child == 0) {
	pthread_t* pth;
        pth = (pthread_t*)malloc(3 * sizeof(pthread_t));
	for (i = 0; i < 3; i++) {
		*j = i;
		if (pthread_create(&pth[i], NULL, threadFunc, &j) == -1)
			printf("thread fail\n");
		
	}
	for (i = 0; i < 3; i++) {
		pthread_join(pth[i], NULL);
	}
    }
    else {
        pthread_t* pth;
	wait(NULL);
	printf("parent started\n");
        pth = (pthread_t*)malloc(3 * sizeof(pthread_t));
	for (i = 3; i < 6; i++) {
		*j = i;
		if (pthread_create(&pth[i-3], NULL, threadFunc, &j) == -1)
			printf("thread fail\n");
	}
	for (i = 0; i < 3; i++) {
		pthread_join(pth[i], NULL);
	}
    }
    return 0;
}
