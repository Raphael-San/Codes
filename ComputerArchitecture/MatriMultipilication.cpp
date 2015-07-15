#include<iostream>
#include<ctime>
using namespace std;

const int size = 1000;

int main()
{
	int **A = new int*[size];
	int **B = new int*[size];
	int **result = new int*[size];
	int **result2 = new int*[size];
	int **transpose = new int*[size];

	for (int i = 0; i < size; i++)
		A[i] = new int[size]();
	
	for (int i = 0; i < size; i++)
		B[i] = new int[size]();

	for (int i = 0; i < size; i++)
		result[i] = new int[size]();

	for (int i = 0; i < size; i++)
		result2[i] = new int[size]();

	for (int i = 0; i < size; i++)
		transpose[i] = new int[size]();
	
	//随机赋值
	srand((int)time(0));
	for (int i = 0; i < size;i++)
	for (int j = 0; j < size; j++)
	{
		A[i][j] = rand() % 100;
		B[i][j] = rand() % 100;
	}

	//矩阵乘
	time_t start, end;
	
	start = clock();
	for (int i = 0; i < size;i++)
	for (int j = 0; j < size;j++)
	for (int k = 0; k < size; k++)
		result[i][j] += A[i][k] * B[k][j];

	end = clock();

	cout << "正常方法所花费的时间： "<<(double)(end - start)<<"  MS" << endl;
	
	start = clock();
	for (int i = 0; i < size;i++)
	for (int j = 0; j < size;j++)
		transpose[i][j]=B[j][i];

	for (int i = 0; i < size;i++)
	for (int j = 0; j < size; j++)
	for (int k = 0; k < size;k++)
		result2[i][j] += A[i][k] * transpose[j][k];
	end = clock();
	cout << "采用转置矩阵所需要花费的时间： "<<(double)(end - start) << "   ms" << endl;

	cout << "输出数组前十个数据，验证结果是否正确 ：" << endl;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << result[i][j] << " ";

		cout << endl;
	}

	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << result2[i][j] << " ";

		cout << endl;
	}
	
	return 0;
}