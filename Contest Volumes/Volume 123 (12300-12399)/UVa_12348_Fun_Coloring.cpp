
/*
	UVa 12348 - Fun Coloring

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12348_Fun_Coloring.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;

const int n_max = 22, m_max = 111, nr_members_max = 3;

struct set {
	int nr_members_;
	int members_[nr_members_max];
} sets[m_max];

int k, n, m;
char colors[n_max + 1];

bool coloring(int mi);

inline bool coloring(int mi, int ci, char rbi)
{
	char pci = colors[ci];
	colors[ci] = rbi;
	bool result = coloring(mi + 1);
	colors[ci] = pci;
	return result;
}

inline bool coloring(int mi, int ci, char rbi, int cj, char rbj)
{
	char pci = colors[ci], pcj = colors[cj];
	colors[ci] = rbi; colors[cj] = rbj;
	bool result = coloring(mi + 1);
	colors[ci] = pci; colors[cj] = pcj;
	return result;
}

inline bool coloring(int mi, int ci, char rbi, int cj, char rbj, int ck, char rbk)
{
	char pci = colors[ci], pcj = colors[cj], pck = colors[ck];
	colors[ci] = rbi; colors[cj] = rbj; colors[ck] = rbk;
	bool result = coloring(mi + 1);
	colors[ci] = pci; colors[cj] = pcj; colors[ck] = pck;
	return result;
}

bool coloring(int mi)
{
	if (mi == m) {
#ifdef DEBUG
		for (int i = 1; i <= n; i++)
			cout << colors[i] << ' ';
		cout << endl;
#endif
		return true;
	}
	else {
		set& st = sets[mi];
		if (st.nr_members_ < 1)
			return false;
		int ci = st.members_[0];
		if (st.nr_members_ < 2) {
			if (colors[ci])
				return coloring(mi + 1);
			else {
				if (coloring(mi, ci, 'R'))
					return true;
				return coloring(mi, ci, 'B');
			}
		}
		int cj = st.members_[1];
		if (st.nr_members_ < 3) {
			if (colors[ci] && colors[cj]) {
				if (colors[ci] == colors[cj])
					return false;
				else
					return coloring(mi + 1);
			}
			else if (!colors[ci] && colors[cj])
				return coloring(mi, ci, (colors[cj] == 'R') ? 'B': 'R');
			else if (colors[ci] && !colors[cj])
				return coloring(mi, cj, (colors[ci] == 'R') ? 'B': 'R');
			else {
				if (coloring(mi, ci, 'R', cj, 'B'))
					return true;
				return coloring(mi, ci, 'B', cj, 'R');
			}
		}
		int ck = st.members_[2];
		char rb;
		if (colors[ci] && colors[cj] && colors[ck]) {
			if (colors[ci] == colors[cj] && colors[ci] == colors[ck])
				return false;
			else
				return coloring(mi + 1);
		}
		else if (!colors[ci] && colors[cj] && colors[ck]) {
			if (colors[cj] ==  colors[ck])
				return coloring(mi, ci, (colors[cj] == 'R') ? 'B' : 'R');
			else {
				if (coloring(mi, ci, 'R'))
					return true;
				return coloring(mi, ci, 'B');
			}
		}
		else if (colors[ci] && !colors[cj] && colors[ck]) {
			if (colors[ci] == colors[ck])
				return coloring(mi, cj, (colors[ci] == 'R') ? 'B' : 'R');
			else {
				if (coloring(mi, cj, 'R'))
					return true;
				return coloring(mi, cj, 'B');
			}
		}
		else if (colors[ci] && colors[cj] && !colors[ck]) {
			if (colors[ci] == colors[cj])
				return coloring(mi, ck, (colors[ci] == 'R') ? 'B' : 'R');
			else {
				if (coloring(mi, ck, 'R'))
					return true;
				return coloring(mi, ck, 'B');
			}
		}
		else if (!colors[ci] && !colors[cj] && colors[ck]) {
			rb = (colors[ck] == 'R') ? 'B' : 'R';
			if (coloring(mi, ci, rb, cj, rb))
				return true;
			if (coloring(mi, ci, 'R', cj, 'B'))
				return true;
			return coloring(mi, ci, 'B', cj, 'R');
		}
		else if (!colors[ci] && colors[cj] && !colors[ck]) {
			rb = (colors[cj] == 'R') ? 'B' : 'R';
			if (coloring(mi, ci, rb, ck, rb))
				return true;
			if (coloring(mi, ci, 'R', ck, 'B'))
				return true;
			return coloring(mi, ci, 'B', ck, 'R');
		}
		else if (colors[ci] && !colors[cj] && !colors[ck]) {
			rb = (colors[ci] == 'R') ? 'B' : 'R';
			if (coloring(mi, cj, rb, ck, rb))
				return true;
			if (coloring(mi, cj, 'R', ck, 'B'))
				return true;
			return coloring(mi, cj, 'B', ck, 'R');
		}
		else {
			if (coloring(mi, ci, 'R', cj, 'R', ck, 'B'))
				return true;
			if (coloring(mi, ci, 'R', cj, 'B', ck, 'R'))
				return true;
			if (coloring(mi, ci, 'B', cj, 'R', ck, 'R'))
				return true;
			if (coloring(mi, ci, 'B', cj, 'B', ck, 'R'))
				return true;
			if (coloring(mi, ci, 'B', cj, 'R', ck, 'B'))
				return true;
			return coloring(mi, ci, 'R', cj, 'B', ck, 'B');
		}
	}
}

int main()
{
	cin >> k;
	while (k--) {
		cin >> n >> m;
		string s;
		getline(cin, s);
		for (int i = 0; i < m; i++) {
			getline(cin, s);
			istringstream iss(s);
			set& st = sets[i];
			st.nr_members_ = 0;
			while (iss >> st.members_[st.nr_members_])
				st.nr_members_++;
		}
		memset(colors, 0, sizeof(colors));
		cout << ((coloring(0)) ? 'Y' : 'N');
	}
	return 0;
}

