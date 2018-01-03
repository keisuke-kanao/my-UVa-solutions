
/*
	UVa 1197 - The Suspects

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1197_The_Suspects.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int n_max = 30000;

class union_find {
public:
	void init(int n);
	int find(int i) const;
	int do_union(int i, int j);
		// generate the union of the two sets to which i and j belong and return the representative of the result set
	int get_rank(int i) {return ranks_[find(i)];}
	int nr_sets() const {return s_;}

private:
	int n_; // number of elements
	int s_; // number of sets
	int representatives_[n_max]; // representatives[i] is the representative of a set to which i belongs
 	int ranks_[n_max]; // ranks_[i] is the number of elements in the set to which i belongs
};

void union_find::init(int n)
{
	n_ = s_ = n;
	for (int i = 0; i < n_; i++) {
		representatives_[i] = i;
		ranks_[i] = 1;
	}
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

union_find students;

int main()
{
	while (true) {
		int n, m;
		scanf("%d %d", &n, &m);
		if (!n)
			break;
		students.init(n);
		for (int i = 0; i < m; i++) {
			int k;
			scanf("%d", &k);
			for (int j = 0, p = 0, q = 0; j < k; j++) {
				scanf("%d", &q);
				if (j)
					students.do_union(p, q);
				p = q;
			}
		}
		printf("%d\n", students.get_rank(0));
	}
	return 0;
}

