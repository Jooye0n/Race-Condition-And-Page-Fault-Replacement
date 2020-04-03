#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define PAGENUM 1000
#define FRAMESIZE 10

int full = 0;//To check whether all frames are filled
int reference[PAGENUM + 1];//To take the input
int frame[FRAMESIZE];
int ctr[FRAMESIZE] = { 0 };
static int f = 0;//This is a counter that keeps track of current time
int repptr;
int count = 0;



int display()
{
	int i;

	for (i = 0; i<full; i++)
		printf("%d\t", frame[i]);
	printf("\n");



}
int Longestopt()//Fucntion for discivering the least recently used page using their corresponding counter values
{
	int i, min;
	min = 0;
	for (i = 0; i<FRAMESIZE; i++)
		if (ctr[min]>ctr[i])
			min = i;

	repptr = min;
	return repptr;

}
void Pagerep(int ele)
{
	repptr = Longestopt();//Gets the LRU page from a function
	frame[repptr] = ele;
	ctr[repptr] = f;//When ever a page is brought it's counter is kept as per the current time of use
}
void Pagefault(int ele)
{	
	int tem;
	if (full != FRAMESIZE)
	{
		ctr[full] = f;//Setting the counter as per current time of use
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
				flag = 1; ctr[i] = f;//If page fault doesn't occur, but the element is referenced, it's counter is set to the current time of use
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
		f++;//Time of use is incremented
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
