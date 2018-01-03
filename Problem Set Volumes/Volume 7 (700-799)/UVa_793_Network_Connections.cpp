
/*
	UVa 793 - Network Connections

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_793_Network_Connections.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class union_find {
public:
	union_find(int _n);
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
	string line;
	istringstream iss;
	getline(cin, line);
	iss.str(line);
	int ds;
	iss >> ds;
	iss.clear();
	getline(cin, line); // skip a blank line
	while (ds--) {
		getline(cin, line);
		iss.str(line);
		int n;
		iss >> n;
		iss.clear();
		union_find computers(n + 1);
		int successful = 0, unsuccessful = 0;
		while (getline(cin, line) && !line.empty()) {
			iss.str(line);
			char c;
			int i, j;
			iss >> c >> i >> j;
			if (c == 'c')
				computers.do_union(i, j);
			else {
				if (computers.find(i) == computers.find(j))
					successful++;
				else
					unsuccessful++;
			}
			iss.clear();
		}
		cout << successful << ',' << unsuccessful << endl;
		if (ds)
			cout << endl;
	}
	return 0;
}

