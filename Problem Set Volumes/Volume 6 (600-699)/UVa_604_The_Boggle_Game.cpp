
/*
	UVa 604 - The Boggle Game

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_604_The_Boggle_Game.cpp

	from Pacific Northwest Regionals - 1997
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_PacNW/1997/index.html)
*/

#include <iostream>
#include <set>
#include <cstring>
using namespace std;

const int nr_rows = 4, nr_columns = 4;
const int nr_letters = 4;

char first_board[nr_rows][nr_columns], second_board[nr_rows][nr_columns];
bool visited[nr_rows][nr_columns];

struct pigewu {
	char s_[nr_letters + 1];

	bool operator<(const pigewu& p) const {return strcmp(s_, p.s_) < 0;}
};

inline bool is_vowel(char c)
{
	return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y';
}

void boggle(int r, int c, int l, int vl, pigewu& p, char board[nr_rows][nr_columns], set<pigewu>& pigewus)
{
	const int nr_dirs = 8;
	const int dirs[nr_dirs][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

	p.s_[l++] = board[r][c];
	if (is_vowel(p.s_[l - 1]))
		vl++;
	visited[r][c] = true;
	if (l == nr_letters) {
		p.s_[nr_letters] = '\0';
		pigewus.insert(p);
	}
	else {
		for (int i = 0; i < nr_dirs; i++) {
			int nr = r + dirs[i][0], nc = c + dirs[i][1];
			if (nr < 0 || nr >= nr_rows || nc < 0 || nc >= nr_columns || visited[nr][nc])
				continue;
			bool vowel = is_vowel(board[nr][nc]);
			if (vl == 2 && vowel || l == 2 && vl == 0 && !vowel || l == 3 && vl == 1 && !vowel)
				continue;
			boggle(nr, nc, l, vl, p, board, pigewus);
		}
	}
	visited[r][c] = false;
}

int main()
{
	bool printed = false;
	while (true) {
		char c;
		cin >> c;
		if (c == '#')
			break;
		cin.unget();
		if (printed)
			cout << endl;
		else
			printed = true;
		for (int r = 0; r < nr_rows; r++) {
			for (int c = 0; c < nr_columns; c++)
				cin >> first_board[r][c];
			for (int c = 0; c < nr_columns; c++)
				cin >> second_board[r][c];
		}
		pigewu p;
		set<pigewu> first_pigewus, second_pigewus;
		for (int r = 0; r < nr_rows; r++)
			for (int c = 0; c < nr_columns; c++) {
				memset(visited, 0, sizeof(visited));
				boggle(r, c, 0, 0, p, first_board, first_pigewus);
				memset(visited, 0, sizeof(visited));
				boggle(r, c, 0, 0, p, second_board, second_pigewus);
			}

		size_t nr_first_pigewus = first_pigewus.size(), nr_secont_pigewus = second_pigewus.size();
		bool found = false;
		if (nr_first_pigewus && nr_secont_pigewus) {
			if (nr_first_pigewus > nr_secont_pigewus) {
				for (set<pigewu>::const_iterator i = second_pigewus.begin(), e = second_pigewus.end(); i != e; ++i)
					if (first_pigewus.find(*i) != first_pigewus.end()) {
						found = true;
						cout << i->s_ << endl;
					}
			}
			else {
				for (set<pigewu>::const_iterator i = first_pigewus.begin(), e = first_pigewus.end(); i != e; ++i)
					if (second_pigewus.find(*i) != second_pigewus.end()) {
						found = true;
						cout << i->s_ << endl;
					}
			}
		}
		if (!found)
			cout << "There are no common words for this pair of boggle boards.\n";
	}
	return 0;
}

