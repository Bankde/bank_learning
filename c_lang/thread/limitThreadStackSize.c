#include <pthread.h>
#include <stdio.h>
#define N 1000
#define PI 3.1415926

pthread_attr_t attr;

/* This program should be Segmentation Fault */
/* This is our thread function.  It is like main(), but for a thread*/
void *threadFunc(void *arg)
{
	double A[N][N];
	size_t stackSize;
	char *ans;

	ans = malloc(20);
	strcpy(ans, "Finish running.");

	//pthread_attr_getstacksize(&attr, &stackSize);
	//printf("ThreadStackSize is %d bytes\n", stackSize);

	/* To prevent marvelous OS caching */
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

	pthread_create(&pth,NULL,threadFunc,"foo");
	
	pthread_join(pth, &ans);
	printf("%s\n", ans);
	return 0;
}
