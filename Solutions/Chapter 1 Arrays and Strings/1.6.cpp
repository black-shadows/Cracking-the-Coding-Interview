/*
 *Q1.6 Given an image represented by an N*N matrix,where each pixel int image is 4 bytes,write a method to rotate the image by90 degrees.
 *Can you do this in place?
 *
 *    1   2   3   4                   4   8   12  16
 *    5   6   7   8        -->        3   7   11  15
 *    9   10  11  12                  2   6   10  14
 *    13  14  15  16                  1   5   9   13
 *
 */

#include <iostream>
using namespace std;

void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

void transpose(int a[][4], int n)
{
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			swap(a[i][j], a[j][i]);
	for (int i = 0; i < n / 2; ++i)
		for (int j = 0; j < n; ++j)
			swap(a[i][j], a[n - 1 - i][j]);
}

int main()
{
	int a[4][4] = 
	{
		{1,2,3,4},
		{5,6,7,8},
		{9,10,11,12},
		{13,14,15,16}
	};
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			cout << a[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	transpose(a, 4);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			cout << a[i][j] << " ";
		cout << endl;
	}
	return 0;
}
