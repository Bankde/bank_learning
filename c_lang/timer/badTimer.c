#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define threadNum 10

int *runTable;

double getTimeMs()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (double)((tv.tv_sec) + 0.000001*tv.tv_usec);
}
/* This is our thread function.  It is like main(), but for a thread*/
void *loop(void *arg)
{
	int i;
	i = *(int*)arg;
	while(1)
	{
		usleep(10000);
		// printf("threadFunc runs: %d\n", i);
		runTable[i] = runTable[i] + 1;
	}
	return NULL;
}

void *timer(void *arg)
{
	int old = 0;
	int index = 0;
	int sum = 0;
	while(1)
	{
		usleep(1000000);
		sum = 0; //reset sum because runTable is already accumulated.
		for (index = 0; index < threadNum; index++)
		{
			sum = sum + runTable[index];
		}
		// I don't reset runTable so it won't cause racing condition from multithread-write
		printf("=== Timer Counter: %d \t\tTime: %f ===\n", (sum - old), getTimeMs());
		old = sum;
	}
	return NULL;
}

int main(void)
{
	pthread_t pth[10];	// this is our thread identifier
	pthread_t timer_pth;
	int i = 0;

	runTable = (int *) calloc(threadNum, sizeof(int));

	for (i = 0; i < threadNum; i++)
	{
		pthread_create(&pth[i], NULL, loop, &i);
	}
	pthread_create(&timer_pth, NULL, timer, 0);
	pthread_join(timer_pth, NULL);

	return 0;
}
