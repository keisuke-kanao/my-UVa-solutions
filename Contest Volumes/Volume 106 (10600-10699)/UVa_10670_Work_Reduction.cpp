
/*
	UVa 10670 - Work Reduction

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10670_Work_Reduction.cpp
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int name_chrs_max = 16; // max. agency name length in chars
const int l_max = 100; // max. number of work reduction agencies

struct agency {
	char name_[name_chrs_max + 1];
	int a_, b_; // rates
	int min_cost_;

	bool operator<(const agency& ag) const {
		if (min_cost_ < ag.min_cost_)
			return true;
		else if (min_cost_ > ag.min_cost_)
			return false;
		else
			return strcmp(name_, ag.name_) < 0;
	}
} agencies[l_max];

int calculate_min_cost(int n, int m, int a, int b)
{
	int min_cost = 0;
	while (n - m) {
		if (n / 2 >= m) {
			int cost = (n - n / 2) * a;
			min_cost += (cost >= b) ? b : cost;
			n /= 2;
		}
		else {
			min_cost += (n - m) * a;
			n -= n - m;
		}
	}
	return min_cost;
}

int main()
{
	int t;
	cin >> t;
	for (int tc = 1; tc <= t; tc++) {
		int n, m, l;
		cin >> n >> m >> l;
		memset(agencies, 0, sizeof(agencies));
		for (int i = 0; i < l; i++) {
			string s;
			cin >> s;
			size_t p = s.find(':'), q = s.find(',');
			strncpy(agencies[i].name_, s.c_str(), p);
			agencies[i].a_ = atoi(s.c_str() + p + 1);
			agencies[i].b_ = atoi(s.c_str() + q + 1);
		}
		for (int i = 0; i < l; i++)
			agencies[i].min_cost_ = calculate_min_cost(n, m, agencies[i].a_, agencies[i].b_);
		cout << "Case " << tc << endl;
		sort(agencies, agencies + l);
		for (int i = 0; i < l; i++)
			cout <<agencies[i].name_ << ' ' << agencies[i].min_cost_ << endl;
	}
	return 0;
}

