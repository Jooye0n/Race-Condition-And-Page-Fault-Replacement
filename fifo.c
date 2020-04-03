#include<stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAGENUM 1000
#define FREAMNUM 10

int main()
{
	int i, k;
	int frame[FREAMNUM] = { 0 };
	int reference[PAGENUM] = { 0 };
	int count = 0;
	int j = 0;
	int avail = 0;

	srand(time(NULL));

	for (i = 1; i <= PAGENUM; i++)
		reference[i] = rand() % 1001;

	for (i = 0; i<FREAMNUM; i++)
		frame[i] = -1;

	printf("ref string\t page frames\n");
	for (i = 1; i <= PAGENUM; i++)
	{
		printf("%d\t\t", reference[i]);
		avail = 0;
		for (k = 0; k<FREAMNUM; k++)
			if (frame[k] == reference[i])
				avail = 1;
		if (avail == 0)
		{
			frame[j] = reference[i];
			j = (j + 1) % FREAMNUM;
			count++;

			for (k = 0; k<FREAMNUM; k++)
				printf("%d\t", frame[k]);
		}
		printf("\n");
	}
	printf("Page Fault Is %d\n", count);
	return 0;
}