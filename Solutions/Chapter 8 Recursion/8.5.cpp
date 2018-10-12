/*
 * Q 8.5 Implement an algorithm to print all valid(e.g.,properly opened and closed)combinations of n-pairs of parentheses.
 *EXAMPLE:
 *input:3(e.g.,3 pairs of parentheses)
 *output:((())),(()()),(())(),()(()),()()()
 */

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

void print_pare(int l, int r, char str[], int cnt)
{
	if (l < 0 || r < l) return;
	if (l == 0 && r == 0)
	{
		for (int i = 0;i < cnt; ++i)
		{
			cout << str[i];
		}
		cout << ",";
	}
	else
	{
		if (l > 0)
		{
			str[cnt] = '(';
			print_pare(l - 1,r,str,cnt+1);
		}
		if (r > l)
		{
			str[cnt] = ')';
			print_pare(l, r - 1, str, cnt + 1);
		}
	}
}
int main()
{
    const int cnt = 3;
    char str[2*cnt];
    print_pare(cnt, cnt, str, 0);
    return 0;
}
