#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This is our thread function.  It is like main(), but for a thread*/
void *threadFunc(void *arg)
{
	char *str;
	int i = 0;

	str=(char*)arg;

	while(i < 110 )
	{
		usleep(1);
		printf("threadFunc says: %d\n",i);
		++i;
	}

	char *a = (char*)malloc(20);
	strcpy(a, "Test thread exit");
	pthread_exit(a);
}

int main(void)
{
	pthread_t pth;	// this is our thread identifier
	int i = 0;

	pthread_create(&pth,NULL,threadFunc,"foo");
	
	while(i < 100)
	{
		usleep(1);
		printf("main is running...\n");
		++i;
	}

	printf("main waiting for thread to terminate...\n");
	char *b;
	pthread_join(pth, (void*)&b);
	printf("Return value is %s\n", b);
	return 0;
}
