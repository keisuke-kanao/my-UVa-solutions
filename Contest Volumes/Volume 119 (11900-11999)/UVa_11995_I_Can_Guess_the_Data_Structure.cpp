
/*
	UVa 11995 - I Can Guess the Data Structure!

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11995_I_Can_Guess_the_Data_Structure.cpp
*/

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

enum {ds_stack = 1, ds_queue = 2, ds_priority_queue = 4};

int main()
{
	int n;
	while (cin >> n) {
		int ds = ds_stack | ds_queue | ds_priority_queue;
		stack<int> st;
		queue<int> q;
		priority_queue<int> pq;
		while (n--) {
			int c, e;
			cin >> c >> e;
			if (c == 1) {
				if (ds & ds_stack)
					st.push(e);
				if (ds & ds_queue)
					q.push(e);
				if (ds & ds_priority_queue)
					pq.push(e);
			}
			else {
				if (ds & ds_stack) {
					if (st.empty() || st.top() != e)
						ds &= ~ds_stack;
					else
						st.pop();
				}
				if (ds & ds_queue) {
					if (q.empty() || q.front() != e)
						ds &= ~ds_queue;
					else
						q.pop();
				}
				if (ds & ds_priority_queue) {
					if (pq.empty() || pq.top() != e)
						ds &= ~ds_priority_queue;
					else
						pq.pop();
				}
			}
		}
		if (ds == ds_stack)
			cout << "stack\n";
		else if (ds == ds_queue)
			cout << "queue\n";
		else if (ds == ds_priority_queue)
			cout << "priority queue\n";
		else if (ds)
			cout << "not sure\n";
		else
			cout << "impossible\n";
	}
	return 0;
}

