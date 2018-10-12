/*
 * Q 20.5 You have a large text file containing words. Given any two words,
 * find the shortest distance (in terms of number of words) between them in the file.
 * Can you make the searching operation in O(1) time? 
 * What about the space complexity for your solution?
 */

#include <iostream>
using namespace std;

const int kMaxInt = ~(1 << 31);

int ShortestDist(string text[], int n, string word1, string word2)
{
	int min = kMaxInt / 2;
	int pos1 = -min;
	int pos2 = -min;

	for (int pos = 0; pos < n; ++pos)
	{
		if (text[pos] == word1)
		{
			pos1 = pos;
			int dist = pos1 - pos2;
			if (dist < min)
				min = dist;
		}
		else if (text[pos] == word2)
		{
			pos2 = pos;
			int dist = pos2 - pos1;
			if (dist < min)
				min = dist;
		}
	}
	return min;
}

int main()
{
	string text[] = { "To","be","Or","not","to","be","This","is","a","question" };
	int len = 10;
	cout << ShortestDist(text, len, "Or", "is") << endl;
	return 0;
}
