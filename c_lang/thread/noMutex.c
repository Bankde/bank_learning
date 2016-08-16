#include <pthread.h>
#include <stdio.h>

int globalInt = 0;

/* This is our thread function.  It is like main(), but for a thread*/
void *threadFunc(void *arg)
{
	globalInt = globalInt+1;
	usleep(1);
	globalInt = globalInt*2;
	usleep(1);
	globalInt = globalInt-2;
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t pth[10];	// this is our thread identifier
	int i = 0;

	for (i=0; i < 10; i++)
		pthread_create(&pth[i],NULL,threadFunc,NULL);

	for (i=0; i < 10; i++)
		pthread_join(pth[i], NULL);

	printf("Final value is %d\n", globalInt);

	return 0;
}
