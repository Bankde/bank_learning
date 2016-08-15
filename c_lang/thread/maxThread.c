#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 1024
#define PI 3.1415926
#define newSize N*N*256

/* 
Number of thread in Ubuntu seems to limit at 15339 (less if memory is not enough)
*/

void *threadFunc(void *arg)
{
	int a[N*N*24];
	sleep(1000000);
}

int main(void)
{
	pthread_t pth;	// this is our thread identifier
	int i = 0;
	char *ans;
	size_t stackSize;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	stackSize = newSize;
	pthread_attr_setstacksize(&attr, stackSize);
	
	int rc;

	while(1) {
		rc = pthread_create(&pth, &attr,threadFunc, &attr);
		if(rc) {
			printf("Pthread created fail at %d\n", i);
			return -1;
		}
		i++;
	}
	return 0;
}
