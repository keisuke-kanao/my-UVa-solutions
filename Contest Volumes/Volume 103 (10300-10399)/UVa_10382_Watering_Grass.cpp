
/*
	UVa 10382 - Watering Grass

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10382_Watering_Grass.cpp

	An accepted solution.
*/

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

struct sprinkler {
	double left_, right_;
	bool operator<(const sprinkler& s) const {return left_ < s.left_;}
};

const int nr_sprinklers_max = 10000;
sprinkler sprinklers[nr_sprinklers_max];

int watering_grass(int n, double l)
{
	int ns = 0;
	double left = 0.0, right = 0.0;
	for (int i = 0; i < n; i++) {
		if (sprinklers[i].left_ > left) {
			if (right >= l || sprinklers[i].left_ > right)
				break;
			left = right;
			ns++;
			if (sprinklers[i].right_ > right)
				right = sprinklers[i].right_;
		}
		else if (sprinklers[i].right_ > right)
			right = sprinklers[i].right_;
	}
	return (right >= l) ? ns + 1 : -1;
}

int main()
{
int m = 0;
	int n, w;
	double l;
	while (cin >> n >> l >> w) {
		double dw = static_cast<double>(w);
		int ns = 0;
		bool covered = false;
		double max_right = 0.0;
		for (int i = 0; i < n; i++) {
			int p, r;
			cin >> p >> r;
			if (r * 2 > w) {
				double dp = static_cast<double>(p), dr = static_cast<double>(r);
				double q = sqrt(dr * dr * 4.0 - dw * dw) / 2.0;
				sprinkler& s = sprinklers[ns];
				s.left_ = dp - q; s.right_ = dp + q;
				if (s.left_ <= 0.0 && s.right_ >= l)
					covered = true;
				max_right = max(max_right, s.right_);
				ns++;
			}
		}
		if (covered)
			ns = 1;
		else if (ns) {
			sort(sprinklers, sprinklers + ns);
			if (sprinklers[0].left_ > 0 || max_right < l)
				ns = -1;
			else
				ns = watering_grass(ns, l);
		}
		else
			ns = -1; 
		cout << ns << endl;
	}
	return 0;
}

