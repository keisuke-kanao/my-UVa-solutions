
/*
	UVa 141 - The Spot Game

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_141_The_Spot_Game.cpp
*/

#include <iostream>
#include <vector>
#include <set>
using namespace std;

void rotate_board(int n, const vector< vector<bool> >& board, vector< vector<bool> >& b)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			b[i][j] = board[j][n - i - 1];
}

void generate_pattern(int n, const vector< vector<bool> >& board, vector<char>& pattern)
{
	int pi = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++, pi++) {
			if (board[i][j])
				pattern[pi / 8] |= static_cast<char>(1 << (pi % 8));
			else
				pattern[pi / 8] &= static_cast<char>(~(1 << (pi % 8)));
		}
}

bool append_patterns(int n, const vector< vector<bool> >& board, set< vector<char> >& patterns)
{
	int m = (n * n + 7) / 8;
	vector<char> pattern(m, 0);
	generate_pattern(n, board, pattern);
	pair<set< vector<char> >::iterator, bool> result = patterns.insert(pattern);
	if (!result.second)
		return false;
	vector< vector<bool> > b(board), c(n, vector<bool>(n));
	for (int i = 0; i < 3; i++, b = c) {
		rotate_board(n, b, c); // rotate the board pattern by 90 degrees
		if (c == board)
			break;
		generate_pattern(n, c, pattern);
		result = patterns.insert(pattern);
		if (!result.second)
			return false;
	}
	return true;
}

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		vector< vector<bool> > board(n, vector<bool>(n, false));
		set< vector<char> > patterns;
		int loser = -1;
		for (int i = 0; i < 2 * n; i++) {
			int j, k;
			char c;
			cin >> j >> k >> c;
			if (loser == -1) {
				j--; k--;
				board[j][k] = (c == '+') ? true : false;
				if (!append_patterns(n, board, patterns))
					loser = i;
			}
		}
		if (loser == -1)
			cout << "Draw\n";
		else
			cout << "Player " << ((loser & 1) ? 1 : 2) << " wins on move " << loser + 1 << endl;
	}
	return 0;
}

