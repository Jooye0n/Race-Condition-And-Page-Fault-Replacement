#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAGENUM 1000
#define FRAMESIZE 10

int full = 0;
int reference[PAGENUM + 1];
int ref[FRAMESIZE];
int frame[FRAMESIZE];
int repptr = 0;
int count = 0;

int display()
{
	int i;

	for (i = 0; i<full; i++)
		printf("%d\t", frame[i]);
	printf("\n");


}
void Pagerep(int ele)
{
	
	while (ref[repptr] != 0)
	{
		ref[repptr++] = 0;
		if (repptr == FRAMESIZE)
			repptr = 0;
	}
	frame[repptr] = ele;
	ref[repptr] = 1;

}
void Pagefault(int ele)
{
	int tem;

	if (full != FRAMESIZE)
	{
		ref[full] = 1;
		frame[full++] = ele;
	}
	else
		Pagerep(ele);
}
int Search(int ele)
{
	int i, flag;
	flag = 0;
	if (full != 0)
	{
		for (i = 0; i<full; i++)
			if (ele == frame[i])
			{
				flag = 1; ref[i] = 1;
				break;
			}
	}
	return flag;
}
int main()
{
	int i;
	int rrand;

	srand(time(NULL));

	printf("The number of elements in the reference string are :");
	printf("%d", PAGENUM);
	printf("\n");

	for (i = 1; i <= PAGENUM; i++) {
		rrand = rand() % 101 + rand() % 101 + rand() % 101 + rand() % 101 + rand() % 101 +
			rand() % 101 + rand() % 101 + rand() % 101 + rand() % 101 + rand() % 101;
		reference[i] = rrand;
	}

	for (i = 0; i<PAGENUM; i++)
		printf("%d  ", reference[i]);
	printf("\n\n");
	for (i = 0; i<PAGENUM; i++)
	{
		if (Search(reference[i]) != 1)
		{
			Pagefault(reference[i]);
			display();
			count++;
		}

	}
	printf("\nThe number of page faults are %d\n", count);

	return 0;
}
