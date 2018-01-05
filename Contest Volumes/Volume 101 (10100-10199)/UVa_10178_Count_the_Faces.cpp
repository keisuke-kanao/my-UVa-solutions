
/*
	UVa 10178 - Count the Faces.

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10178_Count_the_Faces.cpp
*/

#include <vector>
#include <cstdio>
#include <cctype>
using namespace std;

struct union_find {
	union_find(int n);
	~union_find() {}
	int find(int i) const;
	void do_union(int i, int j);
		// generate the union of the two sets to which i and j belong and return the representative of the result set

	int n_; // number of elements
	vector<int> representatives_; // representatives[i] is the representative of a set to which i belongs
	vector<int> ranks_; // ranks_[i] is the number of elements in the set to which i belongs
	vector<int> edges_;
};

union_find::union_find(int n)
	: n_(n), representatives_(n), ranks_(n, 1), edges_(n, 0)
{
	for (int i = 0; i < n_; i++)
		representatives_[i] = i;
}

int union_find::find(int i) const // return the representative of a set to which i belongs
{
	return (representatives_[i] == i) ? i : find(representatives_[i]);
}

void union_find::do_union(int i, int j)
// generate the union of the two sets to which i and j belong and return the representative of the result set
{
	int ri = find(i), rj = find(j);
	if (ri == rj) // already in the same set
		edges_[ri]++;
	else if (ranks_[ri] >= ranks_[rj]) {
		ranks_[ri] += ranks_[rj]; ranks_[rj] = 0;
		edges_[ri] += edges_[rj] + 1; edges_[rj] = 0;
		representatives_[rj] = ri;
	}
	else {
		ranks_[rj] += ranks_[ri]; ranks_[ri] = 0;
		edges_[rj] += edges_[ri] + 1; edges_[ri] = 0;
		representatives_[ri] = rj;
	}
}

const int nr_vertices_max = 52;

int main()
{
	int N, E;
	while (scanf("%d %d", &N, &E) != EOF) {
		union_find uf(nr_vertices_max);
		vector<int> nr_edges(nr_vertices_max);
		while (E--) {
			char s[2], t[2];
			scanf("%s %s", s, t);
			int i = ((isupper(s[0])) ? s[0] - 'A' : nr_vertices_max / 2 + s[0] - 'a'),
				j = ((isupper(t[0])) ? t[0] - 'A' : nr_vertices_max / 2 + t[0] - 'a');
			uf.do_union(i, j);
		}
		int nr_faces = 1;
		for (int i = 0; i < nr_vertices_max; i++)
			if (uf.edges_[i])
				nr_faces += uf.edges_[i] - uf.ranks_[i] + 1;
		printf("%d\n", nr_faces);
	}
	return 0;
}

