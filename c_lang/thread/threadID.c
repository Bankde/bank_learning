#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <pthread.h>

// The result is threadID is increasing (so they won't be dup)
// The start value seems to accumulate from any program (OS assign value ?)
// In ubuntu the max and min threadID are:
// max tid: 131071
// min tid: 300

pid_t max;
pid_t min;
void *threadFunc(void *arg)
{
	int num=(int)arg;
	// SYS_gettid is 186 (in amd64)
	pid_t tid = syscall(SYS_gettid);
	if (tid < min) min = tid;
	if (tid > max) max = tid;
	printf("%d -- PID: %d\t\tThreadID: %d\n", num, getpid(), tid);
}

int main(int argc, char** argv)
{
	pthread_t* pth;	// this is our thread identifier
	int i = 0;
	int count = 10;
	pid_t tid = syscall(SYS_gettid);

	min = tid;
	max = tid;
	pth = (pthread_t*)malloc(10 * sizeof(pthread_t));

	if (argc == 2)
		if (atoi(argv[1]) > 0)
		 	count = atoi(argv[1]);


	for(i = 0; i < count; i++)
	{
		// Note that this is not appropriate call
		// pthread_create expect 4th arg as pointer
		// but I throw Integer (because of easy)
		// it works because pointer size is 8 bytes(or 4 in x32)
		// while int is 4 (so the pointer become 0x0, 0x1, 0x2, etc)
		// However don't do this in real work !!
		pthread_create(&pth[i], NULL, threadFunc, i);
	}	

	pthread_join(pth[count-1],NULL);
	printf("%d -- PID: %d\t\tThreadID: %d\n", -1, getpid(), tid);

	printf("max pid: %d\n", max);
	printf("min pid: %d\n", min);
	return 0;
}
