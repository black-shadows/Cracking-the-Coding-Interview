/*
 * Q 9.3 Given a sorted array of n integers that has been rotated an unknown number of times, give an O(log n) algorithm that finds an element in the array.
 * You may assume that the array was originally sorted in increasing order.
 * Example:
 * Input: find 5 in array (15 16 19 20 25 1 3 4 5 7 10 14)
 * Output:8 (the index of 5 in the array)
 */

#include <iostream>
using namespace std;

int search(int a[], int low, int high, int k)
{
	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (a[mid] == k) return mid;
		if (a[mid] >= a[low])
		{
			if (k < a[mid] && k >= a[low])
				high = mid - 1;
			else
				low = mid + 1;
		}
		else
		{
			if (k > a[mid] && k < a[low])
				low = mid + 1;
			else
				high = mid - 1;
		}
	}
	return -1;
}

int main()
{
	int a[12] = {
		15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};
	int b[19] = {
		2,2,2,2,2,2,2,2,3,2,2,2,2,2,2,2,2,2,2};
	cout << search(a, 0, 11, 3) << endl;
	return 0;
}
