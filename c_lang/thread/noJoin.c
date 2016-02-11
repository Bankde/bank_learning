#include <pthread.h>
#include <stdio.h>

/* This is our thread function.  It is like main(), but for a thread*/
void *threadFunc(void *arg)
{
	char *str;
	int i = 0;

	str=(char*)arg;

	while(i < 110 )
	{
		usleep(1);
		printf("threadFunc says: %d\n", i);
		++i;
	}

	return NULL;
}

int main(void)
{
	pthread_t pth;	// this is our thread identifier
	int i = 0;

	pthread_create(&pth,NULL,threadFunc,"foo");
	
	while(i < 100)
	{
		usleep(1);
		printf("main is running...%d\n", i);
		++i;
	}

	printf("main finished\n");

	return 0;
}