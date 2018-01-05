
/*
	UVa 10120 - Gift?!

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10120_Gift.cpp
*/

/*
from http://www.comp.nus.edu.sg/~stevenha/programming/volC1.html#10120 - Gift!:

A DP problem. Frank start from left bank and at iteration i, Frank can only jump 2*i-1 meters

Base case: Initially at iteration 1, Frank can jump 1 meter.

Recursive case: From all stone j that Frank can reach at iteration i, 
then stone[j-2*i-1] and stone[j+2*i+1] also reachable provided that they doesn't fall outside the range [1..N].

Just check whether stone[M] (where the gift is located) is ever reached... 
Stop the algorithm if no more stones can be reached... 
(algorithm will definitely terminate because jump length is always increases, 
it will at one time jump outside range [1..N]).

Now, since N can be very big (up to 10^6), we need to speed up the algorithm by using a special case that 
when N >= 49, no matter where frog Funny put the gift, Frank will be able to reach it. Proof by induction:

if at N = i, all stones will be reachable then 
at N = i+1, all stones will always be reachable too because at that time, 
whatever your jump length is, we can always arrive from any of stone [1..i] to reach stone i+1. 
This special index happens to be 49 in this case...
*/

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int n_max = 64;
bool rocks[2][n_max + 1];
bool reached[n_max + 1][n_max + 1];

int gift(int n)
{
	memset(rocks[0], 0, sizeof(bool) * (n_max + 1));
	memset(reached[n], 0, sizeof(bool) * (n_max + 1));
	rocks[0][1] = reached[n][1] = true;
	bool *pp = rocks[0], *pc = rocks[1], *pr = reached[n];
	for (int jump = 3; ; jump += 2) {
		memset(pc, 0, sizeof(bool) * (n_max + 1));
		bool continuable = false;
		for (int i = 1; i <= n; i++)
			if (pp[i]) {
				if (i - jump >= 1) {
					continuable = true;
					pc[i - jump] = pr[i - jump] = true;
				}
				if (i + jump <= n) {
					continuable = true;
					pc[i + jump] = pr[i + jump] = true;
				}
			}
		if (!continuable)
			break;
		swap(pp, pc);
	}
	int nr_reached = 0;
#ifdef DEBUG
	int nr_unreached = 0;
#endif
	for (int i = 1; i <= n; i++)
		if (pr[i])
			nr_reached++;
#ifdef DEBUG
		else {
			if (nr_unreached)
				cout << ' ';
			nr_unreached++;
			cout << i;
		}
	cout << endl;
#endif
	return nr_reached;
}

int main()
{
	int n_reachable;
	for (n_reachable = 2; n_reachable <= n_max; n_reachable++) {
		int nr_reached = gift(n_reachable);
#ifdef DEBUG
		cout << n_reachable << ": " << nr_reached << endl;
#endif
		if (nr_reached == n_reachable)
			break;
	}
	while (true) {
		int n, m;
		cin >> n >> m;
		if (!n && !m)
			break;
		cout << ((n >= n_reachable || reached[n][m]) ? "Let me try!\n" : "Don't make fun of me!\n");
	}
	return 0;
}

