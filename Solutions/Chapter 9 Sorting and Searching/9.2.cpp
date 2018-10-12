/*
 * Q 9.2  Write a method to sort an array of strings so that all the anagrams are next to each other.
 */

#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

bool cmp(string s1, string s2)
{
	sort(&s1[0],&s1[0]+s1.length());
	sort(&s2[0], &s2[0] + s2.length());
	return s1 < s2;
}

int main()
{
	string s[] = { "axyz","zyxa","evil","live","kcuf","fuck" };
	sort(s, s + 7, cmp);
	for (int i = 0; i < 7; ++i)
		cout << s[i] << endl;
	return 0;
}
