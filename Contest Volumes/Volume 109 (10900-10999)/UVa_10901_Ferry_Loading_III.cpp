
/*
	UVa 10901 - Ferry Loading III

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10901_Ferry_Loading_III.cpp

	from Waterloo ACM Programming Contest September 17, 2005 Problem B
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int m_max = 10000;

struct car {
	int at_; // arrival time
	int ut_; // unloaded time
	int ab_; // arrival bank
} cars[m_max];

int cars_at_left_bank[m_max], cars_at_right_bank[m_max];
	// cars_at_left/right_bank[i] is the index to cars[] that arrives at left/right bank

enum {left, right};

int main()
{
	int c;
	scanf("%d", &c);
	while (c--) {
		int n, t, m;
		scanf("%d %d %d", &n, &t, &m);
		int mlb = 0, mrb = 0; // number of cars that arrives at left/right bank
		for (int i = 0; i < m; i++) {
			char s[8];
			scanf("%d %s", &cars[i].at_, s);
			if (s[0] == 'l') {
				cars[i].ab_ = left;
				cars_at_left_bank[mlb++] = i;
			}
			else {
				cars[i].ab_ = right;
				cars_at_right_bank[mrb++] = i;
			}
		}
		int ft = 0, fb = left;
		for (int ilb = 0, irb = 0; ilb < mlb || irb < mrb; ) {
			int i, b;
			if (ilb < mlb && irb < mrb) {
				int il = cars_at_left_bank[ilb], ir = cars_at_right_bank[irb];
				if (fb == left && cars[il].at_ <= ft)
					i = il;
				else if (fb == right && cars[ir].at_ <= ft)
					i = ir;
				else if (cars[il].at_ < cars[ir].at_)
					i = il;
				else if (cars[il].at_ > cars[ir].at_)
					i = ir;
				else
					i = (fb == left) ? il : ir;
			}
			else if (ilb < mlb)
				i = cars_at_left_bank[ilb];
			else
				i = cars_at_right_bank[irb];
			b = cars[i].ab_;
			if (cars[i].at_ > ft)
				ft += cars[i].at_ - ft;
			if (fb != cars[i].ab_) {
				ft += t;
				fb = cars[i].ab_;
			}
			if (b == left)
				for (int j = 0; ilb < mlb && cars[cars_at_left_bank[ilb]].at_ <= ft && j < n; ilb++, j++)
					cars[cars_at_left_bank[ilb]].ut_ = ft + t;
			else
				for (int j = 0; irb < mrb && cars[cars_at_right_bank[irb]].at_ <= ft && j < n; irb++, j++)
					cars[cars_at_right_bank[irb]].ut_ = ft + t;
			ft += t;
			fb = (fb == left) ? right : left;
		}
		for (int i = 0; i < m; i++)
			printf("%d\n", cars[i].ut_);
		if (c)
			putchar('\n');
	}
	return 0;
}

