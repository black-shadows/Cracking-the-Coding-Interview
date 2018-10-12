/*
 * Q 19.5 The Game of Master is played as below:
 * The computer has dour slots containing balls that are red(R),yellow(Y),green(G)or blue(B).
 * For example:the computer might have RGGB(e.g.,Slot#1 is red,Slot#2 and Slot#3 are green,Slot#4 is blue).
 * You,the user,are trying to guess the solution.You might,for example,guess YRGB.
 * When you guess the correct color for the correct slot,you get a "hit".
 * If you guess a color that exists but is in the wrong slot,you get a "pseudo-hit".
 * For example:the guess YGRB has 2 hits and ine pseudo hit.
 *
 * For each guess,you are told the number of hits and pseudo-hits.Write a method that,given a guess and a solution,
 * returns the number of hits and pseudo hits.
 */

#include <iostream>
#include <cstring>
using namespace std;

struct Result
{
	int hits;
	int pseudo_hits;
};

Result Estimate(const char* solution, const char* guess)
{
	Result res;
	res.hits = 0;
	res.pseudo_hits = 0;
	int solution_mask = 0;
	for (int i = 0; i < 4; ++i)
	{
		solution_mask |= 1 << (solution[i]-'A');

	}
	for (int i = 0; i < 4; ++i)
	{
		if (guess[i] == solution[i])
			++res.hits;
		else if (solution_mask &(1 << (guess[i] - 'A')))
			++res.pseudo_hits;
	}
	return res;
}

int Min(int a, int b)
{
	return a < b ? a : b;
}

Result Estimate1(const char* solution, const char* guess)
{
	Result res;
	res.hits = 0;
	res.pseudo_hits = 0;
	const int num = 26 + 5;
	int guess_count[num], solution_count[num];
	memset(guess_count, 0, sizeof(guess_count));
	memset(solution_count, 0, sizeof(solution_count));
	for (int i = 0; i < 4; ++i)
	{
		if (guess[i] == solution[i])
			++res.hits;
		++guess_count[(int)(guess[i] - 'A')];
		++solution_count[(int)(solution_count[i] - 'A')];
	}
	char color[] = "RGBY";
	for (int i = 0; i < 4; ++i)
	{
		int idx = (int)(color[i] - 'A');
		res.pseudo_hits += Min(guess_count[idx], solution_count[idx]);
	}
	res.pseudo_hits -= res.hits;
	return res;
}

int main()
{
	char solution[] = "RYGB";
	char guess[] = "YRRR";
	Result res = Estimate(solution, guess);
	cout << res.hits << " " << res.pseudo_hits << endl;
	Result res1 = Estimate1(solution, guess);
	cout << res1.hits << " " << res1.pseudo_hits << endl;
	return 0;
}


