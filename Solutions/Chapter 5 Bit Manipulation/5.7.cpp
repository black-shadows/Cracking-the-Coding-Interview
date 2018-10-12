/*
 *Q5.7 An array A[1…n] contains all the integers from 0 to n except for one number which is missing.
 * In this problem, we cannot access an entire integer in A with a single operation.The elements of A are represented in binary,
 * and the only operation we can use to access them is “fetch the jth bit of A[i]”, which takes constant time. 
 *Write code to find the missing integer. Can you do it in O(n) time?
 */

#include <iostream>
#include <cstring>
using namespace std;

int fetch(int a[], int i, int j)
{
	return (a[i] >> j) & 1;//return 0/1
}
int get(int a[], int i)
{
	int ret = 0;
	for (int j = 31; j >= 0; --j)
		ret = (ret << 1) | fetch(a, i, j);
	return ret;
}
int missing(int a[], int n)
{
	bool *b = new bool[n + 1];
	memset(b, false, (n + 1) * sizeof(bool));
	for (int i = 0; i < n; ++i)
		b[get(a, i)] = true;
	for (int i = 0; i < n + 1; ++i)
	{
		if (!b[i]) return 1;
	}
	delete[] b;
}
int fetch1(int a[], int j)
{
	return (a[j/32]>>(j%32))&1;
}
int get1(int a[], int i)
{
	int ret = 0;
	int base = 32 * i;
	for (int j = base + 31; j >= base; --j)
		ret = (ret << 1) | fetch1(a, j);
	return ret;
}
int missing1(int a[], int n)
{
	bool *b = new bool[n + 1];
	memset(b,false,(n+1)*sizeof(bool));
	for (int i = 0; i < n; ++i)
		b[get1(a, i)] = true;
	for (int i = 0; i < n + 1; ++i)
	{
		if (!b[i]) return i;
	}
	delete[] b;
}

int main()
{
	int a[] = {0,1,2,3,4,5,6,7,8,9,10};
	cout << missing(a, 10) << endl;
	cout << missing1(a, 10) << endl;
	return 0;
}
