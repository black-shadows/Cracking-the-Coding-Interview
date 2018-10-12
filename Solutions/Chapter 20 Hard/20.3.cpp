/*
 * Q 20.3 Write a method to randomly generate a set of m integers grom an array of size n.Each element must have probabaility of being chosen.
 */

#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

void Swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}
void PickMRandomly(int a[], int n, int m)
{
	for (int i = 0; i < m; ++i)
	{
		int j = rand() % (n - i) + i;
		Swap(a[i], a[j]);
	}
}
int main()
{
	srand((unsigned)time(0));
	int n = 9, m = 5;
	int a[] = {1,2,3,4,5,6,7,8,9};
	PickMRandomly(a, n, m);
	for (int i = 0; i < m; ++i)
		cout << a[i] << endl;
	return 0;
}
