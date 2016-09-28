#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t r,w;
pthread_t tid;
int readcount;

void initialize()
{
	pthread_mutex_init(&r,NULL);
	pthread_mutex_init(&w,NULL);
	readcount=0;
}

void* reader(void* params)
{
	int waittime = rand() % 5;
	printf("Reader wants to enter\n");
	pthread_mutex_lock(&r);
	readcount++;
	if(readcount==1)
        pthread_mutex_lock(&w);
    printf("Reader is Inside\n");
    pthread_mutex_unlock(&r);
    sleep(waittime);
    pthread_mutex_lock(&r);
    readcount--;
    if(readcount==0)
    	pthread_mutex_unlock(&w);
    pthread_mutex_unlock(&r);
    printf("Reader is leaving\n");

}

void* writer(void* params)
{
	int waittime;
    waittime=rand() % 3;
    printf("\nWriter is trying to enter");
    pthread_mutex_lock(&w);
    printf("\nWrite has entered");
    sleep(waittime);
    pthread_mutex_unlock(&w);    
    printf("\nWriter is leaving");
    sleep(30);
    exit(0);
}

int main()
{
	initialize();
	int n1,n2,i;    
    printf("\nEnter the no of readers: ");
    scanf("%d",&n1);
    printf("\nEnter the no of writers: ");
    scanf("%d",&n2);
    for(i=0;i<n1;i++)
        pthread_create(&tid,NULL,reader,NULL);  
    for(i=0;i<n2;i++)
        pthread_create(&tid,NULL,writer,NULL);
    sleep(30);
    exit(0);
}

