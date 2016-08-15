#include <pthread.h>
#include <stdio.h>
#define N 1000
#define PI 3.1415926

/* This is our thread function.  It is like main(), but for a thread*/
void *threadFunc(void *arg)
{
	double A[N][N];
	size_t stackSize;
	char *ans;
	pthread_attr_t *attr = (pthread_attr_t*)arg;

	ans = malloc(20);
	strcpy(ans, "Finish running.");

	pthread_attr_getstacksize(attr, &stackSize);
	printf("New ThreadStackSize is %d bytes\n", stackSize);

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
	size_t stackSize;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_getstacksize(&attr, &stackSize);
	printf("Default stack size is %d\n", stackSize);
	stackSize = sizeof(double)*N*N + 1000;
	pthread_attr_setstacksize(&attr, stackSize);
	printf("Set stack size to %d\n", stackSize);

	pthread_create(&pth,&attr,threadFunc,&attr);
	
	pthread_join(pth, &ans);
	printf("%s\n", ans);
	return 0;
}
