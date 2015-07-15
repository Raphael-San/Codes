#include<iostream>
#include<ctime>
using namespace std;
#include<sys/time.h>
#include<pthread.h>
#include<numa.h>


const int len = 1024*1024*512;
const int cpunums = 2;
int count;
char *array = new char[len]();
int pid[cpunums];

pthread_t thread[cpunums];
pthread_mutex_t mutex;
int private_count[cpunums*16];

typedef struct  
{
	int id;
    cpu_set_t binding;   
} threadpara;

void* numa_countM(void* para)
{
	threadpara *mypara = (threadpara *)para;
	int id=mypara->id;
	
	sched_setaffinity(pthread_self(),sizeof(cpu_set_t),&(mypara->binding));
	
	int len_per_thread = len / cpunums;
	int start = id*len_per_thread;
	for (int c = start; c < start+len_per_thread;c++)
	if (array[c] == 'M')
		private_count[id*16]++;

	pthread_mutex_lock(&mutex);
	count +=private_count[id*16];
	pthread_mutex_unlock(&mutex);

	return NULL;
}

void numaTest()
{
	struct timeval start1,end1,start2,end2; 
	cpu_set_t local,remote;
	CPU_ZERO(&local);
	CPU_ZERO(&remote);
	CPU_SET(3,&local);
	CPU_SET(24,&remote);

	threadpara *para1 = (threadpara*)malloc(sizeof(threadpara));
	threadpara *para2 = (threadpara*)malloc(sizeof(threadpara));
	para1->id = 0;
	para1->binding = local;

	para2->id=1;
	para2->binding=remote;
	
	pthread_t localthread,remotethread;

	gettimeofday(&start1,NULL);
	pthread_create(&localthread,NULL,numa_countM,(void*)para1);
	pthread_join(localthread,NULL);
	gettimeofday(&end1,NULL);

	gettimeofday(&start2,NULL);
	pthread_create(&remotethread,NULL,numa_countM,(void*)para2);
	pthread_join(remotethread,NULL);
	gettimeofday(&end2,NULL);

	cout << count << endl;
	cout << (unsigned long)((end1.tv_sec-start1.tv_sec)*1000000+end1.tv_usec-start1.tv_usec)<< endl;
	cout << (unsigned long)((end2.tv_sec-start2.tv_sec)*1000000+end2.tv_usec-start2.tv_usec)<< endl;
}

int main()
{

	cpu_set_t current;
	CPU_ZERO(&current);
	CPU_SET(4,&current);
	sched_setaffinity(0,sizeof(cpu_set_t),&current);

	for (int i = 0; i < len; i++)
	{
		if ((i & 1) == 0)
			array[i] = 'P';
		else
			array[i] = 'M';
	}

	for(int i=0;i<cpunums;i++)
	{
		pid[i]=i;
		private_count[i*16]=0;
	}

	numaTest();
	
	return 0;
}