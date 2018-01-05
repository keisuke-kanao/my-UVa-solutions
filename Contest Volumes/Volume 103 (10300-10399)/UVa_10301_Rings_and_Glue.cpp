
/*
	UVa 10301 - Rings and Glue

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10301_Rings_and_Glue.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class union_find {
public:
	union_find(int _n);
	~union_find() {}
	int find(int i) const;
	int do_union(int i, int j);
		// generate the union of the two sets to which i and j belong and return the representative of the result set
	int nr_sets() const {return s_;}
	int max_rank();

private:
	int n_; // number of elements
	int s_; // number of sets
	vector<int> representatives_; // representatives[i] is the representative of a set to which i belongs
	vector<int> ranks_; // ranks_[i] is the number of elements in the set to which i belongs
};

union_find::union_find(int n)
	: n_(n), s_(n), representatives_(n), ranks_(n, 1)
{
	for (int i = 0; i < n_; i++)
		representatives_[i] = i;
}

int union_find::find(int i) const // return the representative of a set to which i belongs
{
	return (representatives_[i] == i) ? i : find(representatives_[i]);
}

int union_find::do_union(int i, int j)
// generate the union of the two sets to which i and j belong and return the representative of the result set
{
	int ri = find(i), rj = find(j);
	if (ri == rj) // already in the same set
		return -1;
	s_--;
	if (ranks_[ri] >= ranks_[rj]) {
		ranks_[ri] += ranks_[rj];
		representatives_[rj] = ri;
		return ri;
	}
	else {
		ranks_[rj] += ranks_[ri];
		representatives_[ri] = rj;
		return rj;
	}
}

int union_find::max_rank()
{
	int max_r = 0;
	for (int i = 0; i < n_; i++)
		if (ranks_[i] > max_r)
			max_r = ranks_[i];
	return max_r;
}

struct ring {
	double x_, y_, r_;
};

int main()
{
	int n_max = 100;
	vector<ring> rings(n_max);
	while (true) {
		int n;
		cin >> n;
		if (n == -1)
			break;
		int max_rings = 0;
		if (n) {
			for (int i = 0; i < n; i++)
				cin >> rings[i].x_ >> rings[i].y_ >> rings[i].r_;
			union_find uf(n);
			for (int i = 0; i < n - 1; i++)
				for (int j = i + 1; j < n; j++) {
					double dx = rings[i].x_ - rings[j].x_, dy = rings[i].y_ - rings[j].y_;
					double d = sqrt(dx * dx + dy * dy);
					if (d >= rings[i].r_ + rings[j].r_ ||
						d + min(rings[i].r_, rings[j].r_) < max(rings[i].r_, rings[j].r_))
						;
					else // the two rings overlap
						uf.do_union(i, j);
				}
			max_rings = uf.max_rank();
		}
		cout << "The largest component contains " << max_rings << ((max_rings == 1) ? " ring.\n" : " rings.\n");
	}
	return 0;
}


