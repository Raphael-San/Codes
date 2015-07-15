#include<iostream>
#include<ctime>
#include<fstream>
using namespace std;

const int size = 20;
const int size2 = 2 * size;

void Divide2(int *x, int*y, int start, int end, int *result)
{
	if (end - start <= 4)
	{
		for (int i = start; i <= end; i++)
		{
			int temp = 0, carry = 0, j = 0;
			for (j = start; j <= end; j++)
			{
				temp = x[j] * y[i] + carry + result[i + j];
				result[i + j] = temp % 10;
				carry = temp / 10;
			}
			result[i + j] += carry;
		}
		return;
	}
	else
	{
		int mid = (start + end) / 2;
		int len = mid - start + 1;
		int limit = 2 * size - start - mid - 1;
		int *restemp = new int[size2]();
		int *ac = new int[size2]();
		int *bd = new int[size2]();
		int i = 0, j = 0, temp = 0, carry = 0, k = 0;
		

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

		Divide2(x, y, mid + 1, end, restemp);
		k = 0;
		for (i = mid+1+mid+1; i <2*size; i++)
		{
			ac[k++] = restemp[i];
			result[i] += restemp[i];
			restemp[i] = 0;
		}

		Divide2(x, y, start, mid, restemp);
		k = 0;
		for (i = start+start; i<=mid+mid+1; i++)
		{
			bd[k++] = restemp[i];
			result[i] += restemp[i];
			restemp[i] = 0;
		}

		//for (i = 0; i < 2 * size; i++)
		//	bd[i] += ac[i];

		for (i = 0; i < 2 * size - start - mid - 1; i++)
		{
			//restemp[start + mid + 1 + i] = bd[i]+ac[i];
			result[start + mid + 1 + i] -= bd[i] + ac[i];
		}

		//for (i = 0; i < 2 * size; i++)
		//	result[i] -= restemp[i];

		result[0] += 20;
		for (i = 1; i < 2 * size - 1; i++)
			result[i] += 18;
		result[i] -= 2;

		temp = 0, carry = 0;
		for (i = 0; i < 2 * size - 1; i++)
		{
			temp = result[i] + carry;
			result[i] = temp % 10;
			carry = temp / 10;
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

	int *multiplier = new int[size];
	int *multiplicand = new int[size];
	int *result = new int[2 * size]();
	int *result2 = new int[2 * size]();
	srand((int)time(0));
	long long i = 0;
	for (i = 0; i < size - 1; i++)
	{
		multiplicand[i] = rand() % 10;
		multiplier[i] = rand() % 10;
	}
	multiplicand[i] = rand() % 9 + 1;
	multiplier[i] = rand() % 9 + 1;
	///*
	for (int i = 0; i < size; i++)
	{
		int carry = 0;
		long long temp = 0;
		long long j = 0;
		for (j = 0; j < size; j++)
		{
			temp = multiplier[i] * multiplicand[j] + carry + result[i + j];
			result[i + j] = temp % 10;
			carry = temp / 10;
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

	///*
	for (int i = 0; i <2 * size; i++)
		cout << result2[i];
	cout << endl;
	//*/
	delete[]multiplier;
	delete[]multiplicand;
	delete[]result;
	delete[]result2;

	return 0;
}