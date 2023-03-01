#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_FUELCOUNTING_THREADS 10 
#define NUMBER_OF_DATAVALIDATION_THREADS 10 
#define NUMBER_OF_FUELTYPE 13
#define GRID_SIZE 200  // it is a 200x200 grid

// Two global variables for total count
int fuel_count[10][13];
int valid_count[10];

int fuelData[GRID_SIZE][GRID_SIZE] = {0};

typedef struct
{
	int thread_number;
	int startRow_or_Column;
	int endRow_or_Column;
} parameters;

/*
 * 1 : 1 - 20
  2 : 21 - 40
  3 : 41 - 60
  4 : 61 - 80
  5 : 81 - 100, i * (20 - 19) to i * 20
 */

void *numOccurances(void *pArg)
{
	int *p = (int *)pArg;
	int j = *p;
	int fuel[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	parameters *args = (parameters *) args;

	printf("Child thread %d occurrence for fuel type 1, 2, ... are: ", j);

	for(int rowCount = j * 20 - 20; rowCount < j * 20; rowCount++) {
		for(int i = 0; i < GRID_SIZE; i++) {
			if(fuelData[rowCount][i] >= 1 && fuelData[rowCount][i] <= 13) {
				fuel[((fuelData[rowCount][i]) - 1)] += 1;
			}
		}
	}
	// Once completed, output result of thread and add to global variable.
	for(int i = 0; i < 13; i++) {
		printf("%d ",fuel[i]);
		fuel_count[j-1][i] = fuel[i];
	}
	printf("\n");
}

void *checkValid(void *pArg)
{
	int *p = (int *)pArg;
	int j = *p;
	int valid = 1;
	for(int rowCount = j * 20 - 20; rowCount < j * 20; rowCount++) {
		for(int i = 0; i < GRID_SIZE; i++) {
			if(fuelData[rowCount][i] < 1 || fuelData[rowCount][i] > 13) {
				valid = 0;
			}
		}
	} 
	if(valid == 1)
		printf("Thread %d: Valid data.\n", j+10);
	else
		printf("Thread %d: INVALID data.\n", j+10);
	// Once completed, output result of thread and add to global variable.
	valid_count[j-1] = valid;
}

int main(int argc, char *argv[])
{
	char filename[100];
	printf("Please enter your filename:\n");
	scanf("%s",filename);

	FILE *myFile;
	myFile = fopen(filename, "r");

	//read file into array
	int i,j;

	if (myFile == NULL)
	{
		printf("Error Reading File\n");
		exit (0);
	}
	for (i = 0; i < GRID_SIZE ; i++)
	{
		for (j =0; j < GRID_SIZE; j++)
		{
			fscanf(myFile, "%d ", &fuelData[i][j] );
		}
	}

	pthread_t workers[NUMBER_OF_FUELCOUNTING_THREADS+NUMBER_OF_DATAVALIDATION_THREADS];
	int tNum[10];
	// create 10 threads for counting the occurance of fuel types
	for(i = 1; i <= NUMBER_OF_FUELCOUNTING_THREADS; i++) {
		tNum[i] = i;
		pthread_create(&workers[i], NULL, numOccurances, &tNum[i]);
	}
	
	// create 10 threads for checking if there exist invalid data
	for(i = 1; i <= NUMBER_OF_DATAVALIDATION_THREADS; i++) {
		tNum[i] = i;
		pthread_create(&workers[i], NULL, checkValid, &tNum[i]);
	}

	// wait for the threads to exit and combine the result and print
	for(i = 1; i < 20; i++) {
		pthread_join(workers[i], NULL);
	}

	printf("Parent Data Validity: ");
	int validity = 1;
	for(i = 0; i < 10; i++) {
		if(valid_count[i] == 0){
			validity = 0;
			break;
		}
	}
	if(validity == 1)
		printf("All valid data.\n");
	else 
		printf("Invalid data exists.\n");

	printf("Parent Fuel Type Count: ");
	for(i = 0; i < 13; i++) {
		int count = 0;
		for(int k = 0; k < 10; k++) {
			count += fuel_count[k][i];
		}
		printf("%d ", count);
	}
	
	pthread_exit(NULL);
	return 0;
}
