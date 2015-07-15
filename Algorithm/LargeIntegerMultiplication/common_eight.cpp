#include<iostream>
#include<ctime>
#include<vector>
#include<fstream>
using namespace std;

size_t size = 125000;


int main()
{
	clock_t start, end;
	long long *multiplier = new long long[size];
	long long *multiplicand = new long long[size];
	long long *result = new long long[2 * size]();

	srand((int)time(0));
	long long i = 0;
	for (i = 0; i < size - 1; i++)
	{
		multiplicand[i] = (rand() % 10000) * 10000 + rand() % 10000;
		multiplier[i] = (rand() % 10000) * 10000 + rand() % 10000;
	}
	multiplicand[i] = (rand() % 9000 + 1000) * 10000 + rand() % 10000;
	multiplier[i] = (rand() % 9000 + 1000) * 10000 + rand() % 10000;

	
	start = clock();
	for (i = 0; i < size; i++)
	{
		int carry = 0;
		long long temp = 0;
		long long j = 0;
		for (j = 0; j < size; j++)
		{
			temp = multiplier[i] * multiplicand[j] + carry + result[i + j];
			result[i + j] = temp % 100000000;
			carry = temp / 100000000;
		}
		result[i + j] = carry;
	}

	end = clock();
	cout << endl;
	cout << (double)(end - start) / CLOCKS_PER_SEC << endl;

	time_t nowtime;
	nowtime = time(NULL);
	char timebuf[26];
	errno_t err;
	struct tm ptr;
	localtime_s(&ptr, &nowtime);
	asctime_s(timebuf, 26, &ptr);

	delete[]multiplier;
	delete[]multiplicand;
	delete[]result;
}