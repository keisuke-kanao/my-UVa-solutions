
/*
	UVa 10534 - Wavio Sequence

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10534_Wavio_Sequence.cpp
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

/*
	Calculate the LIS (Longest Increasing Subsequence) and LDS (Longest Decreasing Subsequence) for 
	the vector of integers of N.
	Let lis[i] be the Longest Increasing Subsequence of integers of i, and
		lds[i] be the Longest Decreasing Subsequence of integers of i.
	Find the position of an integer i such that min(lis[i], lds[i]) is maximized, then:
		the length of longest wavio sequence = 2 * min(lis[i], lds[i]) - 1.
*/

const int n_max = 10000;
int integers[n_max], rintegers[n_max];
int lis[n_max], rlis[n_max];

int lis_binary_search(int length, const int iv[], int i)
{
	int l = 1, h = length, m;
	while (l <= h) {
		m = l + (h - l) / 2;
		if (iv[m] == i)
			return m;
		else if (iv[m] < i)
			l = m + 1;
		else
			h = m - 1;
	}
	return l;
}

int calculate_lis(int n, int iv[], int l[])
{
	static int m[n_max + 1];
		// m[i] is the minimum value of the last element of longest increasing sequence whose length is i
	memset(l, 0, sizeof(int) * n);
	memset(m, 0, sizeof(int) * (n + 1));
	int m_length = 1;
	m[1] = iv[0];
	l[0] = 1;
	for (int i = 1; i < n; i++) {
		if (iv[i] < m[1]) {
			m[1] = iv[i];
			l[i] = 1;
		}
		else if (iv[i] > m[m_length]) {
			m_length++;
			m[m_length] = iv[i];
			l[i] = m_length;
		}
		else {
			int j = lis_binary_search(m_length, m, iv[i]);
				// find j such that m[j - 1] < iv[i] <= m[j]
			m[j] = iv[i];
			l[i] = j;
		}
	}
	return l[n - 1];
}

int main()
{
	int n;
	while (cin >> n) {
		for (int i = 0; i < n; i++) {
			cin >> integers[i];
			rintegers[n - i - 1] = integers[i];
		}
		calculate_lis(n, integers, lis);
		calculate_lis(n, rintegers, rlis);
		int w_max = 0;
		for (int i = 0; i < n; i++)
			w_max = max(w_max, min(lis[i], rlis[n - i - 1]));
		cout << w_max * 2 - 1 << endl;
	}
	return 0;
}

