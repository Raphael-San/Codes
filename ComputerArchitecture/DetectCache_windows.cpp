#include<iostream>
#include<ctime>
using namespace std;
#include<windows.h>

#define min (1024)
#define max (1024*1024*64)
#define SIZE_1MB (1024*1024)

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


void detectCache(int *array, int stride)
{
	int len = stride - 1;
	int times = 1024 * 1024 * 64;
	for (int i = 0; i<times; i++)
		array[(i * 16) & (len)]++; //每隔16的int访问一次，取模为了循环访问
}


int main()
{
	//设置一个足够大的数组,并进行初始化
	int *array = new int[max]();
	for (int i = 0; i < max; i++)
		array[i] = i;

	for (int stride = min; stride <= max; stride += stride)
	{
		LARGE_INTEGER cpu, start2, end2;


		QueryPerformanceFrequency(&cpu);
		QueryPerformanceCounter(&start2);
		
		detectCache(array, stride);
		
		QueryPerformanceCounter(&end2);
		
		lable(stride*sizeof(int));
		cout << (double)(end2.QuadPart - start2.QuadPart) / cpu.QuadPart << endl;
		
		if (stride*sizeof(int) == 2 * SIZE_1MB)
		{
			detectCache(array, stride);
			lable((stride + stride / 2)*sizeof(int));
		}
	}


	return 0;
}