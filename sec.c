#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAGENUM 1000
#define FRAMESIZE 10

int full = 0;//To check whether all frames are filled
int reference[PAGENUM + 1];//To take the input
int ref[FRAMESIZE];//This is for reference bits for each frame
int frame[FRAMESIZE];
int repptr = 0;//Initialised to first frame
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
	
	/*When ever a page needs to be replaced the repptr moves from page to page checking whether it's reference bit is 0 or not, if it is 0 it
	coomes out of the while loop and if it is one, it gives a second chance setting the reference bit to 0*/
	while (ref[repptr] != 0)
	{
		ref[repptr++] = 0;
		if (repptr == FRAMESIZE)
			repptr = 0;
	}
	frame[repptr] = ele;
	ref[repptr] = 1;//The latest page reference, hence it is set to 1

}
void Pagefault(int ele)
{
	int tem;

	if (full != FRAMESIZE)
	{
		ref[full] = 1;//All the ref bits are set to 1 as each frame is being filled firstly
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
				flag = 1; ref[i] = 1;//When ever page reference occurs, it's rference bit is set to 1
				break;
			}
	}
	return flag;
}
int main()
{
	int i;

	srand(time(NULL));

	printf("The number of elements in the reference string are :");
	printf("%d", PAGENUM);
	printf("\n");

	for (i = 0; i <= PAGENUM; i++)
		reference[i] = rand() % 1001;

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