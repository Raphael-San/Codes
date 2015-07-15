#include<iostream>
#include<ctime>
#include<fstream>
using namespace std;

const int size = 12500;
const int size2 = 2 * size;

void Divide2(long long *x, long long*y, long long start, long long end, long long *result)
{
	//不再往下分治
	if (end - start <= 2500)
	{
		for (long long i = start; i <= end; i++)
		{
			int carry = 0;
			long long temp = 0, j = 0;
			for (j = start; j <= end; j++)
			{
				temp = x[j] * y[i] + carry + result[i + j];
				result[i +j] = temp % 10000000;
				carry = temp / 10000000;
			}
			result[i + j] += carry;
		}
		return;
	}
	else
	{
		long long mid = (start + end) / 2;
		long long len = mid - start + 1;
		long long limit = 2 * size - start - mid - 1;
		long long *restemp = new long long[size2]();
		long long *ac = new long long[size2]();
		long long *bd = new long long[size2]();
		int i = 0, j = 0, temp = 0, carry = 0, k = 0;
		
		//各自的低位加高位
		for (i = start; i <= mid; i++)
			ac[k++] = x[i];
		k = 0;
		for (; i <= end; i++)
			ac[k++] += x[i];

		k = 0;
		for (i = start; i <= mid; i++)
			bd[k++] = y[i];
		k = 0;
		for (; i <= end; i++)
			bd[k++] += y[i];


		Divide2(ac, bd, 0, len-1, restemp);
		for (i = 0; i < 2 * size - start - mid - 1; i++)
		{
			result[start + mid + 1 + i] += restemp[i];
			ac[i] = 0;
			bd[i] = 0;
			restemp[i] = 0;
		}

		//高位相乘
		Divide2(x, y, mid + 1, end, restemp);
		k = 0;
		for (i = mid+1+mid+1; i <2*size; i++)
		{
			ac[k++] = restemp[i];
			result[i] += restemp[i];
			restemp[i] = 0;
		}

		//低位相乘
		Divide2(x, y, start, mid, restemp);
		k = 0;
		for (i = start+start; i<=mid+mid+1; i++)
		{
			bd[k++] = restemp[i];
			result[i] += restemp[i];
			restemp[i] = 0;
		}

		//最后一次减法
		for (i = 0; i < limit; i++)
			result[start + mid + 1 + i] -= bd[i] + ac[i];

		//补位去负数
		result[0] += 20000000;
		for (i = 1; i <size2 - 1; i++)
			result[i] += 19999998;
		result[i] -= 2;

		//最后进位调整
		temp = 0, carry = 0;
		for (i = 0; i < size2 - 1; i++)
		{
			temp = result[i] + carry;
			result[i] = temp % 10000000;
			carry = temp / 10000000;
		}
		result[i] += carry;

		delete[]bd;
		delete[]ac;
		delete[]restemp;

	}
}


int main()
{
	clock_t start, end;

	long long *multiplier = new long long[size];
	long long *multiplicand = new long long[size];
	long long *result = new long long[2 * size]();
	long long *result2 = new long long[2 * size]();
	srand((int)time(0));
	long long i = 0;
	//一个数组位储存八位数
	for (i = 0; i < size - 1; i++)
	{
		multiplicand[i] = (rand() % 10000) * 10000 + rand() % 10000;
		multiplier[i] = (rand() % 10000) * 10000 + rand() % 10000;
	}
	multiplicand[i] = (rand() % 9000 + 1000) * 10000 + rand() % 10000;
	multiplier[i] = (rand() % 9000 + 1000) * 10000 + rand() % 10000;
	/*
	for (long long i = 0; i < size; i++)
	{
		int carry = 0;
		long long temp = 0;
		long long j = 0;
		for (j = 0; j < size; j++)
		{
			temp = multiplier[i] * multiplicand[j] + carry + result[i + j];
			result[i + j] = temp % 10000000;
			carry = temp / 10000000;
		}
		result[i + j] += carry;
	}
	for (int i = size - 1; i >= 0; i--)
		cout << multiplicand[i];
	cout << endl;
	for (int i = size - 1; i >= 0; i--)
		cout << multiplier[i];
	cout << endl;
	for (int i = 0; i <2 * size; i++)
		cout << result[i];
	cout << endl;
	//*/
	start = clock();
	Divide2(multiplicand, multiplier, 0, size - 1, result2);
	end = clock();
	//cout << (double)(end - start) / CLOCKS_PER_SEC << endl;

	/*
	for (int i = 0; i <2 * size; i++)
		cout << result2[i];
	cout << endl;
	//*/
	delete[]multiplier;
	delete[]multiplicand;
	delete[]result;
	delete[]result2;
	cout << "位数: " << size * 8 << " 位,  时间为: " << (double)(end - start) / CLOCKS_PER_SEC
		<< " S, " << endl;
	return 0;
}