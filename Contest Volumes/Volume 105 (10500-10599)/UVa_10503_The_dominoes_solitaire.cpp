
/*
	UVa 10503 - The dominoes solitaire

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10503_The_dominoes_solitaire.cpp
*/

#include <iostream>
#include <utility>
using namespace std;

bool dominoes_solitaire(int n, int m, int ni, int l, int r, bool used[], const pair<int, int> pieces[])
{
	if (ni == n)
		return l == r;
	else {
		for (int i = 0; i < m; i++) {
			if (used[i])
				continue;
			if (pieces[i].first == l) {
				used[i] = true;
				if (dominoes_solitaire(n, m, ni + 1, pieces[i].second, r, used, pieces))
					return true;
				used[i] = false;
			}
			if (pieces[i].second == l) {
				used[i] = true;
				if (dominoes_solitaire(n, m, ni + 1, pieces[i].first, r, used, pieces))
					return true;
				used[i] = false;
			}
		}
		return false;
	}
}

int main()
{
	const int m_max = 14;
	pair<int, int> pieces[m_max];
	bool used[m_max];
	while (true) {
		int n, m;
		cin >> n;
		if (!n)
			break;
		cin >> m;
		int i, j, l, r;
		cin >> i >> l; // leftmost piece
		cin >> r >> j; // rightmoset piece
		for (int k = 0; k < m; k++) {
			used[k] = false;
			cin >> i >> j;
			pieces[k] = make_pair(i, j);
		}
		cout << ((dominoes_solitaire(n, m, 0, l, r, used, pieces)) ? "YES\n" : "NO\n");
	}
	return 0;
}

