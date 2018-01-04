
/*
	UVa 12100 - Printer Queue

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12100_Printer_Queue.cpp
*/

#include <iostream>
#include <queue>
using namespace std;

struct job {
	int i_;
	int p_;

	job() {}
	job(int i, int p) : i_(i), p_(p) {}
};

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int n, m;
		cin >> n >> m;
		priority_queue<int> pq;
		queue<job> q;
		for (int i = 0; i < n; i++) {
			int p;
			cin >> p;
			pq.push(p);
			q.push(job(i, p));
		}
		int nr = 0;
		while (true) {
			int p = pq.top(); pq.pop();
			job j;
			while (true) {
				j = q.front(); q.pop();
				if (j.p_ == p)
					break;
				q.push(j);
			}
			nr++;
			if (j.i_ == m)
				break;
		}
		cout << nr << endl;
	}
	return 0;
}

