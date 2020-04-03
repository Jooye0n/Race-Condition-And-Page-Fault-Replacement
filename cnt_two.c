#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/time.h>

#define MAXLINE 100
#define BUFFSIZE 1024
#define COUNTNUM 100000

void *compute1();
void *compute2();
void *compute3();
char *timeToString();

int count = 0;
int tot = 0;
char fileName[BUFFSIZE] = {0};
int check = 0;

void main()
{
	FILE* fd;
	size_t n;

	int i;
	char buff[BUFFSIZE];
	char operation[MAXLINE] = { 0 };
	pthread_t thread[4];

	int one=1,two=2, three=3;

	printf("<<<Input log file name>>>\n ");
	fgets(buff,BUFFSIZE,stdin);
	sscanf(buff, "%s", fileName);//이름 지정 가능 c file.txt형태
	fd = fopen(fileName, "w");

	if (strcmp(fileName, "") == 0)
	{
		strcat(operation, "There is no input fileName\n");
	}

	else {
		strcat(operation, "File ");
		strcat(operation, fileName);
		strcat(operation, " created\n");
		fclose(fd);
	}

	if (check == 0) {
		while (count < COUNTNUM) {
			pthread_create(&thread[1], NULL, &compute1, &one);
			pthread_create(&thread[2], NULL, &compute2, &two);
			pthread_create(&thread[3], NULL, &compute3, &three);
		}
	}

	for(i=0 ; i<=3; i++)
	{
		if(pthread_join(thread[i],NULL) != 0)
			printf("Joining thread failed\n");
	}

	return ;


}

void *compute1(void *a)
{
	FILE* fd;
	int *thread = (int *)a;

	char temp[MAXLINE] = { 0 };
	char string1[MAXLINE] = { 0 };
	char string2[MAXLINE] = { 0 };
	char s[20];

	struct tm *lt;
	time_t t;
	struct timeval tv;

	if (t = gettimeofday(&tv, NULL) == -1) {
		perror("gettimeofday() error");
		return;
	}

	if ((lt = localtime(&tv.tv_sec)) == NULL) {
		perror("localtime() error");
		return;
	}


	if (count >= COUNTNUM)
		exit(1);

	sprintf(s, "%04d-%02d-%02d %02d:%02d:%02d.%06d",
		lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday,
		lt->tm_hour, lt->tm_min, lt->tm_sec, tv.tv_usec);
	
	check = 1;
	fd = fopen(fileName, "a");
	count++;
	tot++;
	printf("%s[thread %d] count %d : total = %d\n", s, *thread, count, tot);
	strcpy(temp, s);
	strcat(temp," [ thread 1 ] " );
	strcat(temp, " count = ");
	sprintf(string1, "%d", count);
	strcat(temp, string1);
	strcat(temp, " total =" );
	sprintf(string2, "%d", tot);
	strcat(temp, string2);
	strcat(temp, "\n");
	fprintf(fd," %s", temp);

	fclose(fd);
	check = 0;
	
}

void *compute2(void *a)
{
	FILE* fd;
	int *thread = (int *)a;

	char temp[MAXLINE] = { 0 };
	char string1[MAXLINE] = { 0 };
	char string2[MAXLINE] = { 0 };
	char s[20];

	struct tm *lt;
	time_t t;
	struct timeval tv;

	if (t = gettimeofday(&tv, NULL) == -1) {
		perror("gettimeofday() error");
		return;
	}

	if ((lt = localtime(&tv.tv_sec)) == NULL) {
		perror("localtime() error");
		return;
	}


	if (count >= COUNTNUM)
		exit(1);

	sprintf(s, "%04d-%02d-%02d %02d:%02d:%02d.%06d",
		lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday,
		lt->tm_hour, lt->tm_min, lt->tm_sec, tv.tv_usec);
	
	check = 1;


	fd = fopen(fileName, "a");
	count++;
	tot+=2;
	printf("%s[thread %d] count %d : total = %d\n", s, *thread, count, tot);
	strcpy(temp, s);
	strcat(temp, " [ thread 2 ] ");
	strcat(temp, " count = ");
	sprintf(string1, "%d", count);
	strcat(temp, string1);
	strcat(temp, " total =");
	sprintf(string2, "%d", tot);
	strcat(temp, string2);
	strcat(temp, "\n");
	fprintf(fd, " %s", temp);

	fclose(fd);
	check = 0;
}

void *compute3(void *a)
{
	FILE* fd;
	int *thread = (int *)a;

	char temp[MAXLINE] = { 0 };
	char string1[MAXLINE] = { 0 };
	char string2[MAXLINE] = { 0 };
	char s[20];

	struct tm *lt;
	time_t t;
	struct timeval tv;

	if (t = gettimeofday(&tv, NULL) == -1) {
		perror("gettimeofday() error");
		return;
	}

	if ((lt = localtime(&tv.tv_sec)) == NULL) {
		perror("localtime() error");
		return;
	}


	if (count >= COUNTNUM)
		exit(1);

	sprintf(s, "%04d-%02d-%02d %02d:%02d:%02d.%06d",
		lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday,
		lt->tm_hour, lt->tm_min, lt->tm_sec, tv.tv_usec);
	
	check = 1;


	fd = fopen(fileName, "a");
	count++;
	tot-=3;
	printf("%s[thread %d] count %d : total = %d\n", s, *thread, count, tot);
	strcpy(temp, s);
	strcat(temp, " [ thread 3 ] ");
	strcat(temp, " count = ");
	sprintf(string1, "%d", count);
	strcat(temp, string1);
	strcat(temp, " total =");
	sprintf(string2, "%d", tot);
	strcat(temp, string2);
	strcat(temp, "\n");
	fprintf(fd, " %s", temp);

	fclose(fd);
	check = 0;
}
