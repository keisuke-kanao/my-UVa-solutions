
/*
	UVa 10635 - Prince and Princess

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10635_Prince_and_Princess.cpp

	For the implementation of Longest Increasing Sequence algorithm, see the solution for UVa 481 - What Goes Up.
*/

#include <iostream>
#include <vector>
using namespace std;

int ceil_index(const vector<int>& integers, vector<int>& tail_indices, int l, int h, int ii)
{
	int i = integers[ii];
	while (h - l > 1) {
		int m = l + (h - l) / 2;
		if (integers[tail_indices[m]] >= i)
			h = m;
		else
			l = m;
	}
	return h;
}

int lis(int n, const vector<int>& integers, vector<int>& tail_indices, vector<int>& prev_indices)
{
	int tail_length = 0;
	tail_indices[tail_length++] = 0;
	for (int i = 1; i < n; i++) {
		if (integers[i] < integers[tail_indices[0]]) // a new smallest value
			tail_indices[0] = i;
		else if (integers[i] > integers[tail_indices[tail_length - 1]]) { // extend the largest sequence
			prev_indices[i] = tail_indices[tail_length - 1];
			tail_indices[tail_length++] = i;
		}
		else {
			int ci = ceil_index(integers, tail_indices, -1, tail_length - 1, i);
			if (ci)
				prev_indices[i] = tail_indices[ci - 1];
			tail_indices[ci] = i;
		}
	}
	return tail_length;
}

int main()
{
	int t;
	cin >> t;
	for (int nr = 1; nr <= t; nr++) {
		int n, np, nq;
		cin >> n >> np >> nq;
		vector<int> prince(n * n + 1, -1); // (prince[i] == j) means prince's j-th sequence is prince[i]
		for (int i = 0; i <= np; i++) {
			int p;
			cin >> p;
			prince[p] = i;
		}
		vector<int> princess;
		for (int i = 0; i <= nq; i++) {
			int q;
			cin >> q;
			if (prince[q] != -1)
				princess.push_back(prince[q]);
		}
		int nl = princess.size();
		vector<int> tail_indices(nl), prev_indices(nl, -1);
		int length = lis(nl, princess, tail_indices, prev_indices);
		cout << "Case " << nr << ": " << length << endl;
	}
	return 0;
}

