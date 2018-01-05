
/*
	UVa 11235 - Frequent values

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11235_Frequent_values.cpp

	from University of Ulm Local Contest 2007
		(http://www.informatik.uni-ulm.de/acm/Locals/2007/)

	Segment Tree implementation is from "Competitive Programming" page 22 - 24 "2.3.3 Segment Tree".
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

// Segment Tree Library
// The segment tree is stored like a heap array

#define RANGE_SUM 0
#define RANGE_MIN 1
#define RANGE_MAX 2

vector<int> segment_tree;

void init_segment_tree(int N) { // if original array size is N,
	// the required segment_tree array length is 2*2^(floor(log2(N)) + 1);
	int length = (int)(2 * pow(2.0, floor((log((double)N) / log(2.0)) + 1)));
	segment_tree.resize(length, 0); // resize this vector and fill with 0
}

void build_segment_tree(int code, int A[], int node, int b, int e) {
	if (b == e) { // as b == e, either one is fine
		if (code == RANGE_SUM) segment_tree[node] = A[b]; // store value of this cell
		else segment_tree[node] = b; // if RANGE_MIN/MAXIMUM, store index
	}
	else { // recursively compute the values in the left and right subtrees
		int leftIdx = 2 * node, rightIdx = 2 * node + 1;
		build_segment_tree(code, A, leftIdx , b , (b + e) / 2);
		build_segment_tree(code, A, rightIdx, (b + e) / 2 + 1, e );
		int lContent = segment_tree[leftIdx], rContent = segment_tree[rightIdx];
		if (code == RANGE_SUM) // make this segment contains sum of left and right subtree
			segment_tree[node] = lContent + rContent;
		else { // (code == RANGE_MIN/MAXIMUM)
			int lValue = A[lContent], rValue = A[rContent];
			if (code == RANGE_MIN) segment_tree[node] = (lValue <= rValue) ? lContent : rContent;
			else segment_tree[node] = (lValue >= rValue) ? lContent : rContent;
		}
	}
}

int query(int code, int A[], int node, int b, int e, int i, int j) {
	if (i > e || j < b) return -1; // if the current interval does not intersect query interval
	if (b >= i && e <= j) return segment_tree[node]; // if the current interval is inside query interval
	// compute the minimum position in the left and right part of the interval
	int p1 = query(code, A, 2 * node , b , (b + e) / 2, i, j);
	int p2 = query(code, A, 2 * node + 1, (b + e) / 2 + 1, e , i, j);
	// return the position where the overall minimum is
	if (p1 == -1) return p2; // can happen if we try to access segment outside query
	if (p2 == -1) return p1; // same as above
	if (code == RANGE_SUM) return p1 + p2;
	else if (code == RANGE_MIN) return (A[p1] <= A[p2]) ? p1 : p2;
	else return (A[p1] >= A[p2]) ? p1 : p2;
}

const int n_max = 131072, value_max = 131072;
int indices[n_max];
int frequencies[n_max];

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	while (true) {
		int n, q;
		cin >> n;
		if (!n)
			break;
		cin >> q;
		int nr = 0;
		for (int i = 0, f = 0, j = value_max, pj = value_max; i < n; i++, pj = j) {
			cin >> j;
			if (j != pj) {
				if (nr)
					frequencies[nr - 1] = i - indices[nr - 1];
				indices[nr++] = i;
			}
		}
		frequencies[nr - 1] = n - indices[nr - 1];
		indices[nr] = n; // append a sentinel
#ifndef __BRUTE_FORCE__
		init_segment_tree(nr);
		build_segment_tree(RANGE_MAX, frequencies, 1, 0, nr - 1);
#endif
		while (q--) {
			int i, j;
			cin >> i >> j;
			i--;
			j--;
			int ii = distance(indices, lower_bound(indices, indices + nr + 1, i));
			if (indices[ii] != i)
				ii--;
			int ij = distance(indices, lower_bound(indices, indices + nr + 1, j));
			if (indices[ij] != j)
				ij--;
			int max_frequencies = max(min(indices[ii + 1], j + 1) - i, j + 1 - max(indices[ij], i));
#ifndef __BRUTE_FORCE__
			if (++ii <= --ij)
				max_frequencies = max(max_frequencies, frequencies[query(RANGE_MAX, frequencies, 1, 0, nr - 1, ii, ij)]);
#else
			for (ii++; ii < ij; ii++)
				max_frequencies = max(max_frequencies, frequencies[ii]);
#endif
			cout << max_frequencies << endl;
		}
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

