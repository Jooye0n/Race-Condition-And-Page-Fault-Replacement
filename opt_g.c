#include<stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAGENUM 1000
#define FREAMNUM 10

void display(int *frame);

void main()
{
	int reference[PAGENUM] = { 0 };
	int i, j, k, l;
	int fs[FREAMNUM];
	int max, found = 0;
	int lg[FREAMNUM] = { 0 };
	int flag1 = 0, flag2 = 0;
	int page_fault = 0;
	int frame[FREAMNUM] = { 0 };
	int index;
	int rrand;
	
	srand(time(NULL));

	for (i = 1; i <= PAGENUM; i++) {
		rrand = rand() % 101 + rand() % 101 + rand() % 101 + rand() % 101 + rand() % 101 +
			rand() % 101 + rand() % 101 + rand() % 101 + rand() % 101 + rand() % 101;
		reference[i] = rrand;
	}

	for (i = 0; i<FREAMNUM; i++)
	{
		frame[i] = -1;
	}

	for (j = 0; j<PAGENUM; j++)
	{
		flag1 = 0;
		flag2 = 0;

		for (i = 0; i<FREAMNUM; i++)
		{
			if (frame[i] == reference[j])
			{
				flag1 = 1;
				flag2 = 1;
				break;
			}
		}
		if (flag1 == 0)
		{
			for (i = 0; i<FREAMNUM; i++)
			{
				if (frame[i] == -1)
				{
					frame[i] = reference[j];
					flag2 = 1;
					break;
				}
			}
		}

		if (flag2 == 0)
		{
			for (i = 0; i<FREAMNUM; i++)
				lg[i] = 0;
			for (i = 0; i<FREAMNUM; i++)
			{
				for (k = j + 1; k<PAGENUM; k++)
				{
					if (frame[i] == reference[k])
					{
						lg[i] = k - j;
						break;
					}
				}
			}
			found = 0;
			for (i = 0; i<FREAMNUM; i++)
			{
				if (lg[i] == 0)
				{
					index = i;
					found = 1;
					break;
				}
			}
			if (found == 0)
			{
				max = lg[0];
				index = 0;
				for (i = 1; i<FREAMNUM; i++)
				{
					if (max<lg[i])
					{
						max = lg[i];
						index = i;
					}
				}
			}
			frame[index] = reference[j];
			page_fault++;
		}
		display(frame);
	}
	printf("\n num of page faults:%d\n", page_fault);
}
void display(int*frame)
{
	int i;
	printf("\n");
	for (i = 0; i<FREAMNUM; i++)
		printf("\t%d", frame[i]);
}
