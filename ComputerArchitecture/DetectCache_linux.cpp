#include<iostream>
#include<ctime>
using namespace std;
#include<sys/time.h>
#include<linux/types.h>

#define min (1024)
#define max (1024*1024*64)
#define SIZE_1MB (1024*1024)
#define MILLION 1000000

__u64 gettime()
{
       struct timeval tv;
       gettimeofday(&tv,NULL);
        return ((__u64)(tv.tv_sec))*MILLION+tv.tv_usec;
}


void lable(int i)
{
	if (i < 1e3)
		cout << i << "B" << " ";
	else
	{
		if (i < 1e6)
			cout << i / 1024 << "K" << " ";
		else
		{
			if (i < 1e9)
				cout << i / 1048576 << "M" << " ";
			else
				cout << i / 1073741824 << "G" << " ";
		}
	}

}

//程序最关键部分
void detectCache(int *array, int stride)
{
	int len = stride - 1;
	 int times = 64*SIZE_1MB;
	for (int i = 0; i<times; i++)
	{
		array[(i * 16) & (len)]++; //每隔16个int循环访问，即每隔64B大小
	}
}


int main()
{
	int *array = new int[max]();
	for(int i =0;i<max;i++)
		array[i]=i;
	
	
	for (int stride = min; stride <= max; stride += stride)
	{
		__u64 begin,end;
	
		lable(stride*sizeof(int));
		
		begin = gettime();
		detectCache(array,stride);
		end = gettime();
		cout<<end-begin<<endl;
		
		if (stride == 2 * SIZE_1MB / sizeof(int))
		{
			begin = gettime();
			detectCache(array, 3 * SIZE_1MB/sizeof(int));
			end = gettime();
			lable(3 * SIZE_1MB / sizeof(int));
			cout << end-begin << endl;
		}

	}


	return 0;
}
