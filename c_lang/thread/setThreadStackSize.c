#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 1024
#define PI 3.1415926

/*
The stackSize must be multiple of 8*1024*1024 that is not 8*1024*1024 itself
e.g. 16*1024*1024, 24*1024*1024, 64*1024*1024
*/

/* This is our thread function.  It is like main(), but for a thread*/
void *threadFunc(void *arg)
{
	double A[N][N];
	char *ans;
	ans = malloc(20);
	size_t stackSize;
	pthread_attr_t attr = *(pthread_attr_t*)arg;
	
	pthread_attr_getstacksize (&attr, &stackSize);
	printf("New stack size = %li bytes \n", stackSize);

	strcpy(ans, "Finish running.");
	/* To prevent marvelous OS caching like dedup :P*/
	for (int i=0; i < N; i++)
		for (int j=0; j < N; j++)
			A[i][j] = (i+j)/PI;

	pthread_exit(ans);
}

int main(void)
{
	pthread_t pth;	// this is our thread identifier
	int i = 0;
	char *ans;
	size_t stackSize;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_getstacksize(&attr, &stackSize);
	printf("Default stack size is %li\n", stackSize);
	stackSize = 16*N*N;
	pthread_attr_setstacksize(&attr, stackSize);
	printf("Set stack size to %li\n", stackSize);

	pthread_create(&pth, &attr,threadFunc, &attr);
	
	pthread_join(pth, &ans);
	printf("%s\n", ans);
	pthread_attr_destroy(&attr);
	free(ans);
	return 0;
}
