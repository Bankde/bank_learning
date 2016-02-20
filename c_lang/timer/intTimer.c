#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

#define threadNum 10

int *runTable;
timer_t timerid;

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
}

int old=0, sum=0;

void timer(int sig, siginfo_t *si, void *uc)
{
	int index = 0;
	if(si->si_value.sival_ptr != &timerid)
	{
		printf("Syray signal\n");
	}
	else
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

void *timerThread(void *arg)
{
	struct sigevent sev;
	struct itimerspec its;
	struct sigaction sa;

	printf("New thread for counting created\n");

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = timer;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);

	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = SIGUSR1;
	sev.sigev_value.sival_ptr = &timerid;
	timer_create(CLOCK_REALTIME, &sev, &timerid);

	its.it_value.tv_sec = 1;
	its.it_value.tv_nsec = 0;
	its.it_interval.tv_sec = its.it_value.tv_sec;
	its.it_interval.tv_nsec = its.it_value.tv_nsec;

	timer_settime(timerid, 0, &its, NULL);

	while(1)
		sleep(1);
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
	pthread_create(&timer_pth, NULL, timerThread, 0);
	pthread_join(timer_pth, NULL);

	return 0;
}
