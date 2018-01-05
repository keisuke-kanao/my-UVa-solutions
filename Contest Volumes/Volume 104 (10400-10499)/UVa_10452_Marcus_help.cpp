
/*
	UVa 10452 - Marcus, help!

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10452_Marcus_help.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int m, n;
		cin >> m >> n;
		const int n_max = 8, m_max = 8;
		char path[n_max][m_max];
		int i, j, si, sj;
		for (i = 0; i < m; i++)
			for (j = 0; j < n; j++) {
				cin >> path[i][j];
				if (path[i][j] == '@') {
					si = i; sj = j;
				}
			}
		const char* name = "IEHOVA#";
		i = si; j = sj;
		bool printed = false;
		for (const char* p = name; *p; p++) {
			if (printed)
				cout << ' ';
			else
				printed = true;
			char c = *p;
			if (j && path[i][j - 1] == c) {
				cout << "left";
				j--;
			}
			else if (j < n - 1 && path[i][j + 1] == c) {
				cout << "right";
				j++;
			}
			else {
				cout << "forth";
				i--;
			}
		}
		cout << endl;
	}
	return 0;
}

