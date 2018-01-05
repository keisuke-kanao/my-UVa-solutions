
/*
	UVa 10603 - FILL

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10603_Fill.cpp

	An accepted solution.
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include <limits>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int max_capacity = 200;

struct jugs {
	int a_, b_, c_; // a_ liters of a jug, b_ lters of b jug, and c_ liters of c jug
	jugs(int a, int b, int c) : a_(a), b_(b), c_(c) {}
};

int states[max_capacity + 1][max_capacity + 1][max_capacity + 1];
	// stats[i][j][k] is the total amount of waters poured at the state of 
	// i liters of a jug, j liters of b jug, and k liters of c jug
int total_amounts[max_capacity + 1];
	// total_amounts[i] is the minimum total amount for i liters

void pour(int i, int j, int k, int d, int p, queue<jugs>& q)
{
	if (/* p < total_amounts[d] && */ p < states[i][j][k]) {
		states[i][j][k] = p;
		total_amounts[i] = min(total_amounts[i], p);
		total_amounts[j] = min(total_amounts[j], p);
		total_amounts[k] = min(total_amounts[k], p);
		q.push(jugs(i, j, k));
	}
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	int nr_cases;
	cin >> nr_cases;
	while (nr_cases--) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		for (int i = 0; i <= a; i++)
			for (int j = 0; j <= b; j++)
				for (int k = 0; k <= c; k++)
					states[i][j][k] = numeric_limits<int>::max();
		for (int i = 0; i <= d; i++)
			total_amounts[i] = numeric_limits<int>::max();
		queue<jugs> q;
		pour(0, 0, c, d, 0, q);
		while (!q.empty()) {
			jugs j = q.front(); q.pop();
			int s = states[j.a_][j.b_][j.c_], p;
			if (j.a_) {
				if (j.b_ < b) { // pour from jug a to jug b
					p = min(j.a_, b - j.b_);
					pour(j.a_ - p, j.b_ + p, j.c_, d, s + p, q);
				}
				if (j.c_ < c) { // pour from jug a to jug c
					p = min(j.a_, c - j.c_);
					pour(j.a_ - p, j.b_, j.c_ + p, d, s + p, q);
				}
			}
			if (j.b_) {
				if (j.a_ < a) { // pour from jug b to jug a
					p = min(a - j.a_, j.b_);
					pour(j.a_ + p, j.b_ - p, j.c_, d, s + p, q);
				}
				if (j.c_ < c) { // pour from jug b to jug c
					p = min(j.b_, c - j.c_);
					pour(j.a_, j.b_ - p, j.c_ + p, d, s + p, q);
				}
			}
			if (j.c_) {
				if (j.a_ < a) { // pour from jug c to jug a
					p = min(a - j.a_, j.c_);
					pour(j.a_ + p, j.b_, j.c_ - p, d, s + p, q);
				}
				if (j.b_ < b) { // pour from jug c to jug b
					p = min(b - j.b_, j.c_);
					pour(j.a_, j.b_ + p, j.c_ - p, d, s + p, q);
				}
			}
		}
		while (total_amounts[d] == numeric_limits<int>::max())
			d--;
		cout << total_amounts[d] << ' ' << d << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

