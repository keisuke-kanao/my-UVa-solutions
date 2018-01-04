
/*
	UVa 481 - What Goes Up
	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_481_What_Goes_Up.cpp
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

void print_lis(int i, const vector<int>& integers, const vector<int>& prev_indices)
{
	if (prev_indices[i] != -1)
		print_lis(prev_indices[i], integers, prev_indices);
	cout << integers[i] << endl;
}

int main()
{
	int i;
	vector<int> integers;
	while (cin >> i)
		integers.push_back(i);
	int n = integers.size();
	vector<int> tail_indices(n), prev_indices(n, -1);
	int length = lis(n, integers, tail_indices, prev_indices);
	cout << length << "\n-\n";
	print_lis(tail_indices[length - 1], integers, prev_indices);
	return 0;
}

