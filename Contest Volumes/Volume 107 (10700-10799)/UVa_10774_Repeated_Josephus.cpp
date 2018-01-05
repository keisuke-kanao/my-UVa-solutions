
/*
	UVa 10774 - Repeated Josephus

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10774_Repeated_Josephus.cpp
*/

#include <queue>
#include <cstdio>
using namespace std;

int josephus(int n)
{
	queue<int> q;
	for (int i = 1; i <= n; i++)
		q.push(i);
	bool eliminate = false;
	int last;
	while (!q.empty()) {
		last = q.front(); q.pop();
		if (eliminate)
			eliminate = false;
		else {
			eliminate = true;
			q.push(last);
		}
	}
	return last;
}

const int n_max = 30000;

struct repetition {
	int nr_;
	int last_;
} repetitions[n_max + 1];

void repeated_josephus(int n)
{
	if (repetitions[n].nr_ == -1) {
		int last = josephus(n);
		if (last == n) {
			repetitions[n].nr_ = 0; repetitions[n].last_ = n;
		}
		else {
			repeated_josephus(last);
			repetitions[n].nr_ = repetitions[last].nr_ + 1;
			repetitions[n].last_ = repetitions[last].last_;
		}
	}
}

int main()
{
	for (int i = 1; i <= n_max; i++)
		repetitions[i].nr_ = -1;
	int nr_cases;
	scanf("%d", &nr_cases);
	for (int cn = 1; cn <= nr_cases; cn++) {
		int n;
		scanf("%d", &n);
		repeated_josephus(n);
		printf("Case %d: %d %d\n", cn, repetitions[n].nr_, repetitions[n].last_);
	}
	return 0;
}

