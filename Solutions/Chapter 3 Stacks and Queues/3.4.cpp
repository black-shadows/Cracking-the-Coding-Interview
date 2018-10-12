/*
 *Q3.4 In the classic problem of the Towers of Hanoi,you have 3 rods and N disks of different sizes which can slide onto any tower.
 *The puzzle starts with disks sorted in ascending order of size from top to bottom(e.g.,each disk sits on top of an even larger one).
 *You have the following constrains:
 * 1.Only one disk can be moved at a time.
 * 2.A disk is slid off the top of one rod onto the next rod.
 * 3.A disk can only be placed on top of a large disk.
 *Write a program to move the disks from the first rod to the last using Stacks
 */

#include <iostream>
#include <stack>
using namespace std;

struct op
{
	int begin, end;
	char src, bri, dst;
	op() 
	{

	}
	op(int pbegin,int pend,int psrc,int pbri,int pdst):begin(pbegin),end(pend),src(psrc),bri(pbri),dst(pdst)
	{

	}
};

void hanoi(int n, char src, char bri, char dst)
{
	stack<op> st;
	op tmp;
	st.push(op(1, n, src, bri, dst));
	while (!st.empty())
	{
		tmp = st.top();
		st.pop();
		if (tmp.begin != tmp.end)
		{
			st.push(op(tmp.begin, tmp.end - 1, tmp.bri, tmp.src, tmp.dst));
			st.push(op(tmp.end, tmp.end, tmp.src, tmp.bri, tmp.dst));
			st.push(op(tmp.begin, tmp.end - 1, tmp.src, tmp.dst, tmp.bri));
		}
		else
		{
			cout << "Move disk" << tmp.begin << " from" << tmp.src<<" to"<< tmp.dst << endl;
		}
	}
}

int main()
{
	int n = 3;
	hanoi(n,'A','B','C');
	return 0;
}
