
/*
	UVa 910 - TV game

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_910_TV_game.cpp
*/

#include <iostream>
using namespace std;

const int nr_letters = 26, nr_labels = 2, m_max = 30;

struct position {
	bool special_;
	int next_[nr_labels];
} positions[nr_letters];

int nr_ways[m_max + 1][nr_letters];

int main()
{
	int N;
	while (cin >> N) {
		for (int i = 0; i < N; i++) {
			char a, b, c, d;
			cin >> a >> b >> c >> d;
			int p = a - 'A';
			positions[p].next_[0] = b - 'A'; positions[p].next_[1] = c - 'A';
			positions[p].special_ = d == 'x';
		}
		int m;
		cin >> m;
		for (int i = 0; i <= m; i++)
			for (int j = 0; j < N; j++)
				nr_ways[i][j] = 0;
		nr_ways[0][0] = 1;
		for (int i = 1; i <= m; i++)
			for (int j = 0; j < N; j++) {
				nr_ways[i][positions[j].next_[0]] += nr_ways[i - 1][j];
				nr_ways[i][positions[j].next_[1]] += nr_ways[i - 1][j];
			}
		int nr = 0;
		for (int i = 0; i < N; i++)
			if (positions[i].special_)
				nr += nr_ways[m][i];
		cout << nr << endl;
	}
	return 0;
}

