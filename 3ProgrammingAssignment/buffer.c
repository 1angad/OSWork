#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

#define TRUE 1
typedef int buffer_item;
#define BUFFER_SIZE 8

buffer_item START_NUMBER;

int insert_item(buffer_item item);

int remove_item(buffer_item *item);


buffer_item buffer[BUFFER_SIZE];

pthread_mutex_t mutex;
sem_t empty;
sem_t full;

int insertPointer = 0, removePointer = 0;

int sleepTime; // doesn't work weird

void *producer(void *param);
void *consumer(void *param);

int insert_item(buffer_item item) {
    /* Implementation of the insert_item() function */
	sem_wait(&empty);
   	pthread_mutex_lock(&mutex);
   	buffer[insertPointer] = item;
   	// have to add the + 1 otherwise it acts sttrange
   	insertPointer = (insertPointer + 1) % BUFFER_SIZE;
   	pthread_mutex_unlock(&mutex);
   	sem_post(&full);

	return 0;
}


int remove_item(buffer_item *item) {
	/* Implementation of the remove_item function */
	sem_wait(&full);
    	pthread_mutex_lock(&mutex);
    	*item = buffer[removePointer];
    	removePointer = (removePointer + 1) % BUFFER_SIZE;
   	pthread_mutex_unlock(&mutex);
    	sem_post(&empty);

	return 0;
}

int main(int argc, char *argv[])
{
/* 1. Get command line arguments argv[1],argv[2],argv[3],argv[4] */
/* 2. Initialize buffer */
/* 3. Create producer thread(s) */
/* 4. Create consumer thread(s) */
/* 5. Sleep */
/* 6. Exit */

	int producerThreads, consumerThreads;
	int i, j;

	if(argc != 5)
	{
		fprintf(stderr, "Useage: <sleep time> <producer threads> <consumer threads> <start number>\n");
		return -1;
	}

	sleepTime = atoi(argv[1]);
	producerThreads = atoi(argv[2]);
	consumerThreads = atoi(argv[3]);
	START_NUMBER = atoi(argv[4]);

	/* Initialize the synchronization tools */
	pthread_mutex_init(&mutex, NULL);
    	sem_init(&empty, 0, BUFFER_SIZE);
    	sem_init(&full, 0, 0);

	pthread_t pro[producerThreads], con[consumerThreads];
	int proInd[producerThreads], conInd[consumerThreads];
	
	/* Create the producer and consumer threads */
	for (i = 0; i < producerThreads; i++) {
		proInd[i] = i;
		pthread_create(&pro[i], NULL, producer, &proInd[i]);
    	}

    	for (j = 0; j < consumerThreads; j++) {
		conInd[j] = j;
		pthread_create(&con[j], NULL, consumer, &conInd[j]);
    	}

	/* Sleep for user specified time */
	sleep(sleepTime);
	
	for (i = 0; i < producerThreads; i++)
        	pthread_cancel(pro[i]);
   
 	
 	for (j = 0; j < consumerThreads; j++)
        	pthread_cancel(con[j]);


    	pthread_mutex_destroy(&mutex);
    	sem_destroy(&empty);
    	sem_destroy(&full);

	return 0;
}


void *producer(void *param)
{
	/* Implementation of the producer thread -- refer to Figure 5.26 on page 256 */
	int index = *(int *)param;
    	buffer_item item;

	do {
		item = START_NUMBER++;
		insert_item(item);
		printf("Producer gs_P%d produced %d\n", index, item);
		// this part doesn't work, originally it was sleep(sleepTime) but it doesn't work
		sleep(rand() % 10);
    	} while(TRUE);
	
}

void *consumer(void *param)
{
	/* Implementation of the consumer thread -- refer to Figure 5.26 on page 256 */
	int index = *(int *)param;
   	buffer_item item;

  	do {
		remove_item(&item);
		printf("Consumer gs_C%d consumed %d\n", index, item);
		// this part doesn't work, originally it was sleep(sleepTime) but it doesn't work
		sleep(rand() % 10);
        } while(TRUE);

}

