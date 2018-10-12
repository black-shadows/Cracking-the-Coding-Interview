/*
 * Q 9.1 You are given two sorted arrays, A and B, and A has a large enough buffer at the end to hold B. Write a method to merge B into A in sorted order.
 */

#include <iostream>
using namespace std;

void swap(int &a, int &b)
{
	a = a^b;
	b = a^b;
	a = a^b;
}

void merge(int a[], int begin, int mid, int end)
{
	for (int i = begin; i <= mid; ++i)
	{
		if (a[i] > a[mid + 1])
		{
			swap(a[i], a[mid + 1]);
			for (int j = mid + 1; j < end; ++j)
			{
				if (a[j] <= a[j + 1]) break;
				swap(a[j], a[j + 1]);
			}
		}
	}
}

int main()
{
	int a[10] = { 8,9,11,15,17,1,3,5,12,18 };
	int b[10] = {1,2,3,4,5,6,7,8,9,10};
	merge(a,0,4,9);
	for (int i = 0; i < 10; ++i)
		cout << a[i] << " ";
	return 0;
}
