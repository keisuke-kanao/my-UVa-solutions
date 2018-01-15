
/*
	UVa 571 - Jugs

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_571_Jugs.cpp

	from 1997 ACM South Central USA Programming Contest Problem #7
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_SouthCen/1997/Jugs.html#Solution)
*/

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

enum {fill_A, fill_B, empty_A, empty_B, pour_A_B, pour_B_A};

struct jugs {
	int a_, b_;
	stack<char> steps_;

	jugs(int a, int b, char s) : a_(a), b_(b) {steps_.push(s);}
	jugs(int a, int b, char s, const stack<char>& steps) : a_(a), b_(b), steps_(steps) {steps_.push(s);}
};

void print_steps(stack<char>& steps)
{
	const char* instructions[] = {"fill A\n", "fill B\n", "empty A\n", "empty B\n", "pour A B\n", "pour B A\n"};
	if (!steps.empty()) {
		char s = steps.top(); steps.pop();
		print_steps(steps);
		cout << instructions[s];
	}
}

bool push_jugs_state(int a, int b, char s, const stack<char>& steps,
	vector< vector<bool> >& states, queue<jugs>& q)
{
	if (!states[a][b]) {
		states[a][b] = true;
		q.push(jugs(a, b, s, steps));
		return true;
	}
	else
		return false; // do not transfer to the state that has already been transferred before
}

void pour_jugs(int ca, int cb, int n)
{
	vector< vector<bool> > states(ca + 1, vector<bool>(cb + 1, false));
		// states[i][j] is true if the state where the content of A is i and the content of B is j has already been examined
	queue<jugs> q;
	if (ca > n) {
		states[ca][0] = true;
		q.push(jugs(ca, 0, fill_A));
	}
	else {
		states[0][cb] = true;
		q.push(jugs(0, cb, fill_B));
	}
	for ( ; !q.empty(); q.pop()) {
		jugs& j = q.front();
		if (j.b_ == n) {
			print_steps(j.steps_);
			break;
		}
		int a, b, p;
		// if either of the jugs is empty, try pouring to the empty jug, or fill the empty jug
		if (!j.a_) {
			p = min(ca, j.b_);
			push_jugs_state(p, j.b_ - p, pour_B_A, j.steps_, states, q);
			if (j.b_ < cb)
				push_jugs_state(ca, j.b_, fill_A, j.steps_, states, q);
		}
		else if (!j.b_) {
			p = min(j.a_, cb);
			push_jugs_state(j.a_ - p, p, pour_A_B, j.steps_, states, q);
			if (j.a_ < ca)
				push_jugs_state(j.a_, cb, fill_B, j.steps_, states, q);
		}
		// if both of the jugs are not empty, try pouring between jags, or empty the fully-filled jug
		else {
			if (j.a_ < ca) {
				p = min(ca - j.a_, j.b_);
				push_jugs_state(j.a_ + p, j.b_ - p, pour_B_A, j.steps_, states, q);
			}
			else if (j.a_ == ca)
				push_jugs_state(0, j.b_, empty_A, j.steps_, states, q);
			if (j.b_ < cb) {
				p = min(cb - j.b_, j.a_);
				push_jugs_state(j.a_ - p, j.b_ + p, pour_A_B, j.steps_, states, q);
			}
			else if (cb == j.b_)
				push_jugs_state(j.a_, 0, empty_B, j.steps_, states, q);
		}
	}
	cout << "success\n";
}

int main()
{
	int ca, cb, n;
	while (cin >> ca >> cb >> n)
		pour_jugs(ca, cb, n);
	return 0;
}

