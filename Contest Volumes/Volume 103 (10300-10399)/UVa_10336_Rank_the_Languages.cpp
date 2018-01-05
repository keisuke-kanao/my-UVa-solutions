
/*
	UVa 10336 - Rank the Languages

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10336_Rank_the_Languages.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

void bfs(int i, int j, int rows, int columns, vector< vector<char> >& states_map)
{
	const int nr_dirs = 4;
	const int dirs[nr_dirs][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	queue< pair<int, int> > q;
	char c = states_map[i][j];
	states_map[i][j] = 0;
	q.push(make_pair(i, j));
	while (!q.empty()) {
		pair<int, int> p = q.front();
		q.pop();
		for (int k = 0; k < nr_dirs; k++) {
			i = p.first + dirs[k][0]; j = p.second + dirs[k][1];
			if (i < 0 || i >= rows || j < 0 || j >= columns || states_map[i][j] != c)
				;
			else {
				states_map[i][j] = 0;
				q.push(make_pair(i, j));
			}
		}
	}
}

bool compare_state(const pair<char, int>& i, const pair<char, int>& j)
{
	return i.second > j.second;
}

int main()
{
	const int nr_letters = 26;
	int t;
	cin >> t;
	for (int w = 1; w <= t; w++) {
		int columns, rows;
		cin >> rows >> columns;
		vector< vector<char> > states_map(rows, vector<char>(columns));
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				cin >> states_map[i][j];
		vector< pair<char, int> > states(nr_letters);
		for (int i = 0; i < nr_letters; i++)
			states[i] = make_pair(i + 'a', 0);
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				if (states_map[i][j]) {
					states[states_map[i][j] - 'a'].second++;
					bfs(i, j, rows, columns, states_map);
				}
		stable_sort(states.begin(), states.end(), compare_state);
		cout << "World #" << w << endl;
		for (int i = 0; i < nr_letters && states[i].second; i++)
			cout << states[i].first << ": " << states[i].second << endl;
	}
	return 0;
}

