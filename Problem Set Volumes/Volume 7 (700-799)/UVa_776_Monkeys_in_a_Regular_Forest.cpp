
/*
	UVa 776 - Monkeys in a Regular Forest

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_776_Monkeys_in_a_Regular_Forest.cpp
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

void bfs(int nr_rows, int nr_columns, int r, int c, int fn, const vector< vector<char> >& forest, vector< vector<int> >& monkeys)
{
	const int nr_dirs = 8;
	const int dirs[nr_dirs][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
	char fc = forest[r][c];
	queue<pair<int, int> > q;
	monkeys[r][c] = fn;
	q.push(make_pair(r, c));
	while (!q.empty()) {
		pair<int, int> rc = q.front();
		q.pop();
		for (int i = 0; i < nr_dirs; i++) {
			r = rc.first + dirs[i][0]; c = rc.second + dirs[i][1];
			if (r >= 0 && r < nr_rows && c >= 0 && c < nr_columns &&
				forest[r][c] == fc && !monkeys[r][c]) {
				monkeys[r][c] = fn;
				q.push(make_pair(r, c));
			}
		}
	}
}

int main()
{
	string line;
	while (getline(cin, line)) {
		vector< vector<char> > forest;
		do {
			if (line[0] == '%')
				break;
			forest.push_back(vector<char>());
			istringstream iss(line);
			char c;
			while (iss >> c)
				forest.back().push_back(c);
		} while (getline(cin, line));
		int nr_rows = static_cast<int>(forest.size()), nr_columns = static_cast<int>(forest[0].size());
		vector< vector<int> > monkeys(nr_rows, vector<int>(nr_columns, 0));
		for (int r = 0, fn = 0; r < nr_rows; r++)
			for (int c = 0; c < nr_columns; c++)
				if (!monkeys[r][c])
					bfs(nr_rows, nr_columns, r, c, ++fn, forest, monkeys);
		vector<int> widths(nr_columns, 0);
		for (int c = 0; c < nr_columns; c++) {
			for (int r = 0; r < nr_rows; r++) {
				int fn = monkeys[r][c], w = ((c) ? 1 : 0);
				do {
					fn /= 10;
					w++;
				} while (fn);
				widths[c] = max(widths[c], w);
			}
		}
		cout << setfill(' ');
		for (int r = 0;r < nr_rows; r++) {
			for (int c = 0; c < nr_columns; c++)
				cout << setw(widths[c]) << monkeys[r][c];
			cout << endl;
		}
		cout << "%\n";
	}
	return 0;
}

