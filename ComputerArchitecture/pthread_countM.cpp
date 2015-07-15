#include<iostream>
#include<ctime>
using namespace std;
#include<sys/time.h>
#include<pthread.h>


const int len = 1024*1024*512;
const int cpunums = 1;
int count;
char *array = new char[len]();
int pid[cpunums];

pthread_t thread[cpunums];
pthread_mutex_t mutex;
int private_count[cpunums*16];


void* countM_thread(void* arg)
{
	int id = *(int*)arg;
	int len_per_thread = len / cpunums;
	int start = id*len_per_thread;
	for (int c = start; c < start+len_per_thread;c++)
	if (array[c] == 'M')
		count++;

	return NULL;
}

void* countM_thread2(void* arg)
{
	int id = *(int*)arg;
	int len_per_thread = len / cpunums;
	int start = id*len_per_thread;
	for (int c = start; c < start+len_per_thread;c++)
	if (array[c] == 'M')
	{
		pthread_mutex_lock(&mutex);
		count++;
		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}


void* countM_thread3(void* arg)
{
	int id = *(int*)arg;
	int len_per_thread = len / cpunums;
	int start = id*len_per_thread;
	
	for (int c = start; c < start+len_per_thread;c++)
	//这里则是反复操作多次
	if (array[c] == 'M')
		private_count[id*16]++;

	//在这里只是操作了一次
	//pthread_mutex_lock(&mutex);
	//count +=private_count[id*16];
	//pthread_mutex_unlock(&mutex);

	//所以在不在这里在，还是拿到主线程加，其实都是不会有太大的差别

	return NULL;
}


void count_with_thread()
{
	for (int i = 0; i < cpunums; i++)
		pthread_create(&thread[i], NULL, countM_thread,(void*)&pid[i]);

	for (int j = 0; j < cpunums; j++)
		pthread_join(thread[j], NULL);
}

int main()
{
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
	
	pthread_mutex_init(&mutex, NULL);   
	
	struct timeval start,end;
	gettimeofday(&start,NULL);
	
	count_with_thread();

	//for(int total=0;total<cpunums;total++)
	//	count+=private_count[total*16];

	gettimeofday(&end,NULL);
	cout<<"cpu: "<<cpunums<<endl;
	cout << count << endl;
	cout << (unsigned long)((end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec)<< endl; 
	
	return 0;
}