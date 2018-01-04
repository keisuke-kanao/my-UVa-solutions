
/*
	UVa 11503 - Virtual Friends

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11503_Virtual_Friends.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class union_find {
public:
	union_find(int _n);
	~union_find() {}
	int find(int i) const;
	int do_union(int i, int j);
		// generate the union of the two sets to which i and j belong and return the representative of the result set
	int nr_sets() const {return s_;}
	int get_rank(int i) const {return ranks_[i];}

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

int register_friend(const string&s, map<string, int>& identifiers)
{
	pair< map<string, int>::iterator, bool> result = identifiers.insert(make_pair(s, static_cast<int>(identifiers.size())));
	return result.first->second;
}

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int f;
		cin >> f;
		union_find friends(f * 2);
		map<string, int> identifiers;
		while (f--) {
			string s, t;
			cin >> s >> t;
			int i = register_friend(s, identifiers), j = register_friend(t, identifiers);
			friends.do_union(i, j);
			cout << friends.get_rank(friends.find(i)) << endl;
		}
	}
	return 0;
}

