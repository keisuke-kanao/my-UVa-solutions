
/*
	UVa 10227 - Forests

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10227_Forests.cpp

	from University of Waterloo Local Contest - 26 January 2002, Problem D
		(http://acm.student.cs.uwaterloo.ca/~acm00/020126/data/)
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
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

const int P_max = 100, T_max = 100;
bool falls[P_max][T_max]; // falls[i][j] is true if people i has heard tree j fall

int main()
{
	string line;
	istringstream iss;
	getline(cin, line);
	iss.str(line);
	int nr_cases;
	iss >> nr_cases;
	iss.clear();
	getline(cin, line); // skip a blank line
	while (nr_cases--) {
		getline(cin, line);
		iss.str(line);
		int P, T;
		iss >> P >> T;
		iss.clear();
		for (int i = 0; i < P; i++)
			for (int j = 0; j < T; j++)
				falls[i][j] = false;
		while (getline(cin, line) && !line.empty()) {
			iss.str(line);
			int i, j;
			iss >> i  >> j;
			iss.clear();
			falls[i - 1][j - 1] = true;
		}
		union_find opinions(P);
		for (int i = 0; i < P - 1; i++)
			for (int j = i + 1; j < P; j++) {
				int k;
				for (k = 0; k < T; k++)
					if (falls[i][k] != falls[j][k])
						break;
				if (k == T) // i and i has the same opinions
					opinions.do_union(i, j);
			}
		cout << opinions.nr_sets() << endl;
		if (nr_cases)
			cout << endl;
	}
	return 0;
}

