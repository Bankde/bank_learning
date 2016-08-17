#include <pthread.h>
#include <stdio.h>

int globalInt = 0;
pthread_mutex_t myMutex;
pthread_cond_t oddTurn;
pthread_cond_t evenTurn;

/*
Need to use WHILE instead of an IF because https://computing.llnl.gov/tutorials/pthreads/
"If several threads are waiting for the same wake up signal, they will take turns acquiring the mutex, and any one of them can then modify the condition they all waited for. "
Note: make sure you understand the term "take turn".
Using WHILE or IF depends on application. (WHILE is recommended as it is usually safer)

Signal will only wake up 1 thread that matches the cond (randomly picked by system)
Broadcast will wake all threads.
Try switching (comment/uncomment) signal and broadcast to understand the behavior.
*/

void *addOdd(void *arg)
{
	int tid = (int)arg;
	pthread_mutex_lock(&myMutex);
	while (globalInt % 2 == 0) {
		printf("%d (odd): I have to wait\n", tid);
		pthread_cond_wait(&oddTurn, &myMutex);
	}
	globalInt++;
	pthread_cond_signal(&evenTurn);
	// broadcast will wake all threads, doesn't need in this case
	// pthread_cond_broadcast(&evenTurn);
	printf("%d (odd): Im finished, send signal\n", tid);
	pthread_mutex_unlock(&myMutex);
	pthread_exit(NULL);
}

void *addEven(void *arg)
{
	int tid = (int)arg;
	pthread_mutex_lock(&myMutex);
	while (globalInt % 2 == 1) {
		printf("%d (even): I have to wait\n", tid);
		pthread_cond_wait(&evenTurn, &myMutex);
	}
	globalInt++;
	pthread_cond_signal(&oddTurn);
	// pthread_cond_broadcast(&oddTurn);
	printf("%d (even): Im finished, send signal\n", tid);
	pthread_mutex_unlock(&myMutex);
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t pth[20];	// this is our thread identifier
	pthread_mutex_init(&myMutex, NULL);
	pthread_cond_init(&oddTurn, NULL);
	pthread_cond_init(&evenTurn, NULL);
	int i = 0;

	for (i=0; i < 10; i++)
		pthread_create(&pth[i],NULL,addOdd,i);

	for (i=10; i < 20; i++)
		pthread_create(&pth[i],NULL,addEven,i);

	for (i=0; i < 20; i++)
		pthread_join(pth[i], NULL);

	printf("Final value is %d\n", globalInt);

	pthread_mutex_destroy(&myMutex);
	pthread_cond_destroy(&oddTurn);
	pthread_cond_destroy(&evenTurn);
	return 0;
}
