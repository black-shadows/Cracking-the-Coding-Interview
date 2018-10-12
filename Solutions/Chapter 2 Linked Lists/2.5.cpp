/*
 *Q2.5 Given a circular linked list,implement an algorithm which returns node at the beginning of the loop.
 *DEFINITION
 *Circular linked list: A (corrupt) linked list in which a node’s next pointer points to an earlier node, so as to make a loop in the linked list.
 *EXAMPLE
 *Input: A -> B -> C -> D -> E -> C [the same C as earlier]
 *Output:C
 */

#include <iostream>
#include <map>
using namespace std;

typedef struct node 
{
	int data;
	node *next;
}node;

node* init(int a[], int n, int m)
{
	node *head, *p, *q;
	for (int i = 0; i < n; ++i)
	{
		node *nd = new node();
		nd->data = a[i];
		if (i == m) q = nd;
		if (i == 0)
		{
			head = p = nd;
			continue;
		}
		p->next = nd;
		p = nd;
	}
	p->next = q;
	return head;
}

node* loopstart(node *head)
{
	if (head == NULL) return NULL;
	node *fast = head, *slow = head;
	while (fast&&fast->next)
	{
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow) break;
	}
	if (!fast || !fast->next) return NULL;
	slow = head;
	while (fast != slow)
	{
		fast = fast->next;
		slow = slow->next;
	}
	return fast;
}

map<node*, bool> hash1;
node* loopstart1(node *head)
{
	while (head)
	{
		if (hash1[head]) return head;
		else
		{
			hash1[head] = true;
			head = head->next;
		}
	}
	return head;
}

int main()
{
	int n = 10, m = 9;
	int a[] = { 3, 2, 1, 3, 5, 6, 2, 6, 3, 1 };
	node *head = init(a,n,m);
	node *p = loopstart1(head);
	if (p)
		cout << p->data << endl;
	return 0;
}

