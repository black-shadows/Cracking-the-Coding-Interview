/*
 *Q1.8 Assume you have a method isSubstring which checks if one word is a substring of another.
 *Given two things,s1 and s2,write code to check if s2 is a rotation of s1 using only one call
 *to isSubstring(i.e.,"waterbottlde"is a rotation of"erbottlewat").
 */

#include <iostream>
#include <string>
using namespace std;

bool isSubstring(string s1, string s2)
{
	if (s1.find(s2) != string::npos) return true;
	else return false;
}

bool isRotation(string s1, string s2)
{
	if (s1.length() != s2.length() || s1.length() <= 0)
		return false;
	return isSubstring(s1+s2,s2);
}

int main()
{
	string s1 = "apple";
	string s2 = "pleap";
	cout << isRotation(s1, s2) << endl;
	return 0;
}
