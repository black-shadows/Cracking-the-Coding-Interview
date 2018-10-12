/*
 *Q3.6 Write a program to sort a stack in ascending order.You should not make any assumptions about how the stack is impletmented.
 *The following are the only functions that should be used to write this program:push|pop|peek|isEmpty.
 */

#include <iostream>
#include <cstdlib>
#include <functional>
#include <ctime>
#include <stack>
#include <queue>
using namespace std;

void Qsort(stack<int> &s) {
	priority_queue< int, vector<int>, greater<int> > q;
	while (!s.empty())
	{
		q.push(s.top());
		s.pop();
	}
	while (!q.empty())
	{
		s.push(q.top());
		q.pop();
	}
}

stack<int> Ssort(stack<int>s)
{
	stack<int> t;
	while (!s.empty())
	{
		int data = s.top();
		s.pop();
		while (!t.empty() && t.top() > data)
		{
			s.push(t.top());
			t.pop();
		}
		t.push(data);
	}
	return t;
}

int main()
{
	srand((unsigned)time(0));
	stack<int> s;

	for (int i = 0; i < 10; ++i)
		s.push((rand()%100));

	Qsort(s);
	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}
	return 0;
}
