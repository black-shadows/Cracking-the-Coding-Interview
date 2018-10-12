/*
 * Q 19.4 Write a method which finds the maximum of two numbers. You should not use if-else or any other comparison operator.
 */

#include <iostream>
using namespace std;

int Max1(int a, int b)
{
	int c[2] = { a,b };
	int z = a - b;
	z = (z >> 31) & 1;
	return c[z];
}

int Max2(int a, int b)
{
	int z = a - b;
	int k = (z >> 31) & 1;
	return a - k*z;
}

int main()
{
	int a = 5, b = 10;
	cout << Max1(a, b) << endl;
	cout << Max2(a, b) << endl;
	return 0;
}
