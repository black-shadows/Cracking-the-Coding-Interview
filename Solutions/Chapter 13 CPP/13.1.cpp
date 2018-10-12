/*
 * Q 13.1 Write a method to print the last K lines of an input file using C++.
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void printLastKLines(ifstream &fin, int k)
{
	//std::string *line = new line[k];
	std::string line[k];
	int lines = 0;
	string tmp;
	while (getline(fin, tmp))
	{
		line[line%k] = tmp;
		++lines;
	}
	int start, cnt;
	if (lines < k)
	{
		start = 0;
		cnt = lines;
	}
	else
	{
		start = lines%k;
		cnt = k;
	}
	for (int i = 0; i < cnt; ++i)
		cout << line[(start + i) % k] << endl;
}
int main()
{
	ifstream fin("13.3.in");
	int k = 4;
	printLastKLines(fin,k);
	fin.close();
	return 0;
}
