#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>

#define MAXLINE 100
#define BUFFSIZE 1024
#define COUNTNUM 100000

pthread_mutex_t mutex_lock;

void *compute();

int count = 0;
int tot = 0;
char fileName[BUFFSIZE] = {0};

void main()
{
	FILE* fd;
	size_t n;

	int i;
	char buff[BUFFSIZE];
	char operation[MAXLINE] = { 0 };
	pthread_t thread[3];
	int status;

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

	pthread_mutex_init(&mutex_lock, NULL);
	
	
	pthread_create(&thread[1], NULL, &compute, &one);
	pthread_create(&thread[2], NULL, &compute, &two);
	pthread_create(&thread[3], NULL, &compute, &three);
	

	pthread_join(thread[1], (void *)&status);
	pthread_join(thread[2], (void *)&status);
	pthread_join(thread[3], (void *)&status);


	pthread_mutex_destroy(&mutex_lock);
	return ;


}

void *compute(void *a)
{
	pthread_mutex_lock(&mutex_lock);
	count = 0;

	FILE* fd;
	int *thread = (int *)a;

	char temp[MAXLINE] = { 0 };
	char string0[MAXLINE] = { 0 };
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

	sprintf(s, "%04d-%02d-%02d %02d:%02d:%02d.%06d",
		lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday,
		lt->tm_hour, lt->tm_min, lt->tm_sec, tv.tv_usec);
	
	while (count < COUNTNUM) {

		fd = fopen(fileName, "a");
		count++;
		tot++;
		printf("%s[thread %d] count %d : total = %d\n", s, *thread, count, tot);
		strcpy(temp, s);
		strcat(temp, " [ thread = ");
		sprintf(string0, "%d", *thread);
		strcat(temp, string0);
		strcat(temp, "] ");
		strcat(temp, " count = ");
		sprintf(string1, "%d", count);
		strcat(temp, string1);
		strcat(temp, " total =");
		sprintf(string2, "%d", tot);
		strcat(temp, string2);
		strcat(temp, "\n");
		fprintf(fd, " %s", temp);

		fclose(fd);
	}
	

	pthread_mutex_unlock(&mutex_lock);
	
}
