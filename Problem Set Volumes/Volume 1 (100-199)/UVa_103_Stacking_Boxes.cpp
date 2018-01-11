
/*
	UVa 103 - Stacking Boxes

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_103_Stacking_Boxes.cpp
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

struct box {
	int nr_;
	vector<int> measurements_;
	box(int n) : nr_(-1), measurements_(n) {}
};

bool compare_box(const box& i, const box& j)
{
	return i.measurements_[0] < j.measurements_[0];
}

bool can_be_nested(int n, const box& i, const box& j)
{
	const vector<int>& im = i.measurements_, jm = j.measurements_;
	for (int k = 0; k < n; k++)
		if (im[k] >= jm[k])
			return false;
	return true;
}

pair<int, int> lis(int k, int n, const vector<box>& boxes, vector<int>& l, vector<int>& prev)
{
	int length = 1, iend = 0;
	l[0] = 1;
	prev[0] = -1;
	for (int i = 1; i < k; i++) {
		l[i] = 1;
		prev[i] = -1;
		for (int j = 0; j < i; j++)
			if (can_be_nested(n, boxes[j], boxes[i])) {
				if (l[i] < 1 + l[j]) {
					l[i] = 1 + l[j];
					prev[i] = j;
				}
			}
		if (length < l[i]) {
			length = l[i];
			iend = i;
		}
	}
	return make_pair(length, iend);
}

void print_box_numbers(const vector<box>& boxes, const vector<int>& prev, int i, int iend)
{
	if (prev[i] != -1)
		print_box_numbers(boxes, prev, prev[i], iend);
	cout << boxes[i].nr_ << ((i == iend) ? '\n' : ' ');;
}

int main()
{
	int k, n;
	while (cin >> k >> n) {
		vector<box> boxes(k, box(n));
		for (int i = 0; i < k; i++) {
			boxes[i].nr_ = i + 1;
			for (int j = 0; j < n; j++)
				cin >> boxes[i].measurements_[j];
			sort(boxes[i].measurements_.begin(), boxes[i].measurements_.end());
		}
		sort(boxes.begin(), boxes.end(), compare_box);
		vector<int> l(k), prev(k);
		pair<int, int> result = lis(k, n, boxes, l, prev);
		cout << result.first << endl;
		print_box_numbers(boxes, prev, result.second, result.second);
	}
	return 0;
}

