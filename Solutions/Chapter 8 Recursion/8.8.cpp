/*
 * Q 8.8 Eight Queens
 * Write an algorithm to print all ways of arranging eight queens on a chess board so that none of them share the same row, column or diagonal.
 */

#include <iostream>
using namespace std;

int c[20], n = 8, cnt = 0;
void print()
{
	for(int i=0;i<n;++i)
		for (int j = 0; j < n; ++j)
		{
			if (j == c[i]) cout << "1 ";
			else cout << "0 ";
		}
	cout << endl;
}
void search(int r)
{
	if (r == n)
	{
		print();
		++cnt;
		return;
	}
	for (int i = 0; i < n; ++i)
	{
		c[r] = i;
		int ok = 1;
		for(int j=0;j<r;++j)
			if (c[r] == c[j] || r - j == c[r] - c[j] || r - j == c[j] - c[r])
			{
				ok = 0;
				break;
			}
		if (ok) search(r + 1);
	}
}
int main()
{
	search(0);
	cout << cnt << endl;
	return 0;
}
