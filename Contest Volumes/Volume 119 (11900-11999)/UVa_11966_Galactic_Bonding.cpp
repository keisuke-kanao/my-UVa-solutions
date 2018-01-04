
/*
	UVa 11966 - Galactic Bonding

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11966_Galactic_Bonding.cpp
*/

#include <iostream>
#include <vector>
using namespace std;

struct point {
	double x_, y_;
};

double square_distance(const point& p1, const point& p2)
{
	double dx = p1.x_ - p2.x_, dy = p1.y_ - p2.y_;
	return dx * dx + dy * dy;
}

class union_find {
public:
	union_find(int n);
	~union_find() {}
	int find(int i) const;
	int do_union(int i, int j);
		// generate the union of the two sets to which i and j belong and return the representative of the result set
	int nr_sets() const {return s_;}

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

int main()
{
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		int N;
		double D;
		cin >> N >> D;
		vector<point> points(N);
		for (int i = 0; i < N; i++)
			cin >> points[i].x_ >> points[i].y_;
		double DS = D * D;
		union_find uf(N);
		for (int i = 0; i < N - 1; i++)
			for (int j = i + 1; j < N; j++)
				if (square_distance(points[i], points[j]) <= DS)
					uf.do_union(i, j);
		cout << "Case " << t << ": " << uf.nr_sets() << endl;
	}
	return 0;
}

/*
SAMPLE INPUT

2
5 1.5
1.0 0.1
2.0 0.0
5.0 0.2
6.0 0.4
3.0 -0.1
3 4.0
121.12 254.06
645.04 301.85
912.49 568.96

SAMPLE OUTPUT

Case 1: 2
Case 2: 3
*/

