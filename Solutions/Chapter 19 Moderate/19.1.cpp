/*
 * Q 19.1 Write a function to swap a number in place without temporary variables.
 */

#include <iostream>
using namespace std;

void swap1(int &a, int &b)
{
	a = a^b;
	b = a^b;
	a = a^b;
}

void swap2(int &a, int &b)
{
	b = a - b;
	a = a - b;
	b = a + b;
}

void swap3(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

int main()
{
	int a = 123;
	int b = 456;
	swap1(a, b);
	cout << a << endl;
	cout << b << endl;
}
