#include<iostream>
#include<ctime>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

size_t size = 100000;

//把整型转换成string
string IntToString(int * a, int n)
{
	string s;
	stringstream ss(s);
	for (int i = 0; i < n; i++)
	{
		ss << a[i];
	}
	s += ss.str();
	return s;
}

//在string0位前面补0..
void fillZero(string &a, int n)
{
	for (int i = 0; i < n; i++)
		a.insert(0, "0");
}

//在string长度末尾补0
void fillZerobefore(string &a, int n)
{
	long long len = a.length();
	string temp;
	for (int i = 0; i < n; i++)
		temp += "0";
	a.insert(len, temp);
}

//两个string相减的操作..
string strminus(string a, string b)
{
	long long len = 0;
	long long reallen = 0;
	for (long long i = a.length() - 1; i >= 0; i--)
	{
		if (a[i] != '0')
		{
			reallen = i;
			break;
		}
	}
	a = a.substr(0, reallen + 1);
	reallen = 0;
	for (long long i = b.length() - 1; i >= 0; i--)
	{
		if (b[i] != '0')
		{
			reallen = i;
			break;
		}
	}
	b = b.substr(0, reallen + 1);
	if (a.length()>b.length())
	{
		len = a.length();
		int *restemp = new int[len]();
		string result;
		long long i = 0;
		for (i = 0; i < b.length(); i++)
		{
			int tempa = a[i] - 48;
			int tempb = b[i] - 48;
			if (tempa >= tempb)
				restemp[i] = tempa - tempb;
			else
			{
				tempa = tempa + 10;
				a[i + 1] = (a[i + 1] - 48) - 1 + 48;
				restemp[i] = tempa - tempb;
			}
		}
		for (; i < len; i++)
			restemp[i] = a[i] - 48;
		result = IntToString(restemp, len);
		delete[]restemp;
		return result;
	}
	else if (a.length() == b.length())
	{
		len = a.length();
		int *restemp = new int[len]();
		string result;
		long long i = 0;
		int flag = 0;
		for (i = len - 1; i >= 0; i--)
		{
			if ((a[i] - 48) > (b[i] - 48))
			{
				flag = 1;
				break;
			}
			else if ((a[i] - 48) < (b[i] - 48))
			{
				flag = 2;
				break;
			}
		}
		if (flag == 1)
		{
			for (long long i = 0; i < len; i++)
			{
				int tempa = a[i] - 48;
				int tempb = b[i] - 48;
				if (tempa >= tempb)
					restemp[i] = tempa - tempb;
				else
				{
					tempa = tempa + 10;
					a[i + 1] = (a[i + 1] - 48) - 1 + 48;
					restemp[i] = tempa - tempb;
				}
			}
			result = IntToString(restemp, len);
			delete[]restemp;
			return result;
		}
		else if (flag == 2)
		{
			for (long long i = 0; i < len; i++)
			{
				int tempa = a[i] - 48;
				int tempb = b[i] - 48;
				if (tempb >= tempa)
					restemp[i] = tempb - tempa;
				else
				{
					tempb = tempb + 10;
					b[i + 1] = (b[i + 1] - 48) - 1 + 48;
					restemp[i] = tempb - tempa;
				}
			}
			result = IntToString(restemp, len);
			delete[]restemp;
			result.insert(result.length(), "-");
			return result;
		}
		else
		{
			result = IntToString(restemp, len);
			delete[]restemp;
			return result;
		}
	}
	else
	{
		len = b.length();
		int *restemp = new int[len]();
		string result;
		long long i = 0;
		for (i = 0; i < a.length(); i++)
		{
			int tempa = a[i] - 48;
			int tempb = b[i] - 48;
			if (tempb >= tempa)
				restemp[i] = tempb - tempa;
			else
			{
				tempb = tempb + 10;
				b[i + 1] = (b[i + 1] - 48) - 1 + 48;
				restemp[i] = tempb - tempa;
			}
		}
		for (; i < len; i++)
			restemp[i] = b[i] - 48;
		result = IntToString(restemp, len);
		delete[]restemp;
		result.insert(result.length(), "-");
		return result;
	}

}

//两个string进行相加..
string strAccumulate(string a, string b)
{
	if (a[a.length() - 1] == '-')
	{
		a = a.substr(0, a.length() - 1);
		string result = strminus(b, a);
		return result;
	}
	else if (b[b.length() - 1] == '-')
	{
		b = b.substr(0, b.length() - 1);
		string result = strminus(a, b);
		return result;
	}
	else
	{
		long long len = 0;
		if (a.length() >= b.length())
		{
			len = a.length();
			int *restemp = new int[len + 1]();
			string result;
			int carry = 0;
			for (long long i = 0; i < len + 1; i++)
			{
				long long temp = 0, j = 0;
				if (i == len)
				{
					restemp[i] = carry;
				}
				else
				{
					if (i >= b.length())
					{
						restemp[i] = a[i] - 48 + carry;
						carry = restemp[i] / 10;
					}
					else
					{
						temp = (a[i] - 48) + (b[i] - 48) + carry;
						carry = temp / 10;
						restemp[i] = temp % 10;
					}
				}
			}
			result = IntToString(restemp, len + 1);
			delete[]restemp;
			return result;
		}
		else
		{
			len = b.length();
			int *restemp = new int[len + 1]();
			string result;
			int carry = 0;
			for (long long i = 0; i < len + 1; i++)
			{
				long long temp = 0, j = 0;
				if (i == len)
				{
					restemp[i] = carry;
				}
				else
				{
					if (i >= a.length())
					{
						restemp[i] = b[i] - 48 + carry;
						carry = restemp[i] / 10;
					}
					else
					{
						temp = (a[i] - 48) + (b[i] - 48) + carry;
						carry = temp / 10;
						restemp[i] = temp % 10;
					}
				}
			}
			result = IntToString(restemp, len + 1);
			delete[]restemp;
			return result;
		}
	}
}


//两个string进行相乘.
string mul(string x, string y)
{
	long long len1 = 0, len2 = 0;
	for (long long i = x.length() - 1; i >= 0; i--)
	{
		if (x[i] != '0')
		{
			len1 = i;
			break;
		}
	}
	len1 += 1;
	x = x.substr(0, len1);
	for (long long i = y.length() - 1; i >= 0; i--)
	{
		if (y[i] != '0')
		{
			len2 = i;
			break;
		}
	}
	len2 += 1;
	y = y.substr(0, len2);
	string result;
	if (len1 <= 4 || len2 <= 4)
	{
		int *restemp = new int[len1 + len2]();
		for (long long i = 0; i < len1; i++)
		{
			int carry = 0;
			long long temp = 0, j = 0;
			for (j = 0; j < len2; j++)
			{
				temp = (x[i] - 48) * (y[j] - 48) + carry + restemp[i + j];
				restemp[i + j] = temp % 10;
				carry = temp / 10;
			}
			restemp[i + j] += carry;
		}
		result = IntToString(restemp, len1 + len2);
		delete[]restemp;
		return result;
	}
	else
	{
		if (len1 > len2)
		{
			fillZerobefore(y, len1 - len2);
			len2 = len1;
		}
		else if (len1 < len2)
		{
			fillZerobefore(x, len2 - len1);
			len1 = len2;
		}
		if (len1 % 2 != 0)
		{
			fillZerobefore(x, 1);
			fillZerobefore(y, 1);
			len1 += 1;
			len2 += 1;
		}

		long long mid = len1 / 2;
		string b = x.substr(0, mid);
		string a = x.substr(mid, len1 - 1);
		string d = y.substr(0, mid);
		string c = y.substr(mid, len2 - 1);
		string ac = mul(a, c);//高位..
		string bd = mul(b, d);//低位..
		//string ad = mul(a, d);//一高一低..
		//string cb = mul(c, b);//一高一低..
		//cout << ac << endl;
		//string resmid = strAccumulate(ad, cb);
		//fillZero(resmid, mid);
		//cout << resmid << endl;
		string aplusb = strAccumulate(a, b);
		string cplusd = strAccumulate(c, d);
		string abcd = mul(aplusb, cplusd);
		//(a+b)(c+d)-(ac+bd)..
		string midimpro = strminus(abcd, strAccumulate(ac, bd));
		//乘于10的n/2次方
		fillZero(midimpro, mid);
		//乘于10的N次方..
		fillZero(ac, len1);
		//相加..
		result = strAccumulate(strAccumulate(ac, midimpro), bd);
		//result = strAccumulate(strAccumulate(ac, resmid), bd);
		return result;
	}

}


int main()
{
	clock_t start, end;
	
	string multiplier;
	string multiplicand;
	int *result;
	result = new int[2 * size]();
	//对两个乘数进行初始化操作..
	srand((int)time(0));
	int i = 0;
	for (i = 0; i < size - 1; i++)
	{
		multiplicand.append(1, rand() % 10 + 48);
		multiplier.append(1, rand() % 10 + 48);
	}
	
	multiplicand.append(1, rand() % 9 + 1 + 48);
	multiplier.append(1, rand() % 9 + 1 + 48);

	start = clock();
	
	//普通相乘..
	/*
	for (i = 0; i < size; i++)
	{
	int carry = 0, j = 0, temp = 0;
	for (j = 0; j < size; j++)
	{
	temp = (multiplier[i] - '0')*(multiplicand[j] - '0')+carry+result[i+j];
	result[i+j] = temp % 10;
	carry = temp / 10;
	}
	result[i + j] += carry;
	}
	*/
	mul(multiplicand, multiplier);
	end = clock();
	cout << (double)(end - start) / CLOCKS_PER_SEC << endl;

	/*
	for (int i = size - 1; i >= 0; i--)
	cout << multiplicand[i];
	cout << endl;
	for (int i = size - 1; i >= 0; i--)
	cout << multiplier[i];
	cout << endl;
	for (int i = 0; i <2*size; i++)
	cout << result[i];
	cout << endl;
	*/
	return 0;
}