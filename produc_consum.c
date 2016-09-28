#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

void* producer(void *arg);
void* consumer(void *arg);
int buffcount = 0;
int buff[20];
sem_t full,empty;

int main()
{
	pthread_t pid,cid;

	sem_init(&empty,0,1);
	sem_init(&full,0,0);

	pthread_create(&pid,NULL,producer,NULL);
	pthread_create(&cid,NULL,consumer,NULL);
	pthread_join(pid,NULL);
	pthread_join(cid,NULL);
}

void* producer(void* arg)
{
	int run = 1;
	while(run)
	{
		sem_wait(&empty);
		sleep(1);
		int x = rand() % 50;
		buff[buffcount++] = x;
		printf("\nProduced Item is:%d\n",buff[buffcount-1]);
		if (buffcount >= 5)
		{
			printf("semaphore set");
			sem_post(&full);
		}
		else
		{
			sem_post(&empty);
		}
	}
	return NULL;
}

void* consumer(void *arg)
{
	int run =1;
	while(run)
	{
		sem_wait(&full);
		sleep(1);
		printf("\nConsumed item is %d\n",buff[buffcount-1]);
		buffcount--;
		if (buffcount <= 0)
		{
			printf("%s\n","semaphore reset");
			sem_post(&empty);
		}
		else
		{
			sem_post(&full);
		}
	}
	return NULL;
}

