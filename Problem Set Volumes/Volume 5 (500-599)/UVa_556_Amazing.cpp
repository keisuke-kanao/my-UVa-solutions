
/*
	UVa 556 - Amazing

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_556_Amazing.cpp
*/

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

const int nr_visited = 5;
enum {north, south, east, west};

int turn_right(int b, int w, vector< vector<char> >& maze, int dir, int i, int j)
{
	int wi, wj;
	switch (dir) {
	case north:
		j++; wi = i + 1; wj = j; break;
	case south:
		j--; wi = i - 1; wj = j; break;
	case east:
		i++; wi = i; wj = j - 1; break;
	case west:
		i--; wi = i; wj = j + 1; break;
	}
	if (i < 0 || i >= b || j < 0 || j >= w || maze[i][j] == '1')
		return dir;
	if (wi < 0 || wi >= b || wj < 0 || wj >= w || maze[wi][wj] == '1') {
		switch (dir) {
		case north:
			dir = east; break;
		case south:
			dir = west; break;
		case east:
			dir = south; break;
		case west:
			dir = north; break;
		}
	}
	return dir;
}

int turn_left(int dir)
{
	switch (dir) {
	case north:
		dir = west; break;
	case south:
		dir = east; break;
	case east:
		dir = north; break;
	case west:
		dir = south; break;
	}
	return dir;
}

bool step_forward(int b, int w, vector< vector<char> >& maze, int dir, int& i, int& j)
{
	int ni = i, nj = j;
	switch (dir) {
	case north:
		ni--; break;
	case south:
		ni++; break;
	case east:
		nj++; break;
	case west:
		nj--; break;
	}
	if (ni < 0 || ni >= b || nj < 0 || nj >= w || maze[ni][nj] == '1')
		return false;
	i = ni; j = nj;
	return true;
}

int main()
{
	while (true) {
		int b, w;
		cin >> b >> w;
		if (!b && !w)
			break;
		vector< vector<char> > maze(b, vector<char>(w));
		vector< vector<int> > visited(b, vector<int>(w, 0));
		for (int i = 0; i < b; i++)
			for (int j = 0; j < w; j++)
				cin >> maze[i][j];
		int si = b - 1, sj = 0, i = b - 1, j = 0, dir = east;
		vector<int> visited_total(nr_visited, 0);
		while (true) {
			dir = turn_right(b, w, maze, dir, i, j);
			if (step_forward(b, w, maze, dir, i, j)) {
				visited[i][j]++;
				if (i == si && j == sj)
					break;
			}
			else
				dir = turn_left(dir);
		}
		for (int i = 0; i < b; i++)
			for (int j = 0; j < w; j++)
				if (maze[i][j] == '0' && visited[i][j] < nr_visited)
					visited_total[visited[i][j]]++;
		for (int i = 0; i < nr_visited; i++)
			cout << setfill(' ') << setw(3) << visited_total[i];
		cout << endl;
	}
	return 0;
}

