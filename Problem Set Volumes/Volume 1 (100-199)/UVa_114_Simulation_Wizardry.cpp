
/*
	UVa 114 - Simulation Wizardry

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_114_Simulation_Wizardry.cpp
*/

#include <iostream>
using namespace std;

const int m_nax = 50, n_max = 50;

int m, n, wall_cost, nr_bumpers;

struct bumper {
	int cost_, point_;
} bumpers[m_nax * n_max + 1];
int grid[m_nax + 1][n_max + 1]; // grid[i][j] is an index to bumpers[] if a bumper is located at (i, j)

enum {dir_right, dir_up, dir_left, dir_down};

void rebound(int& x, int& y, int& direction)
{
	switch (direction) {
	case dir_right:
		x--; break;
	case dir_up:
		y--; break;
	case dir_left:
		x++; break;
	case dir_down:
		y++; break;
	}
	switch (direction) {
	case dir_right:
		direction = dir_down; break;
	case dir_up:
		direction = dir_right; break;
	case dir_left:
		direction = dir_up; break;
	case dir_down:
		direction = dir_left; break;
	}
}

int pinball(int x, int y, int direction, int lifetime)
{
	int points = 0, b;
	while (lifetime > 0) {
		switch (direction) {
		case dir_right:
			x++; break;
		case dir_up:
			y++; break;
		case dir_left:
			x--; break;
		case dir_down:
			y--; break;
		}
		lifetime--;
		if (x == 1 || y == 1 || x == m || y == n) {
			lifetime -= wall_cost;
			rebound(x, y, direction);
		}
		else if (b = grid[x][y]) {
			if (lifetime > 0) {
				points += bumpers[b].point_;
				lifetime -= bumpers[b].cost_;
			}
			rebound(x, y, direction);
		}
	}
	return points;
}

int main()
{
	int x, y, direction, lifetime;
	cin >> m >> n >> wall_cost >> nr_bumpers;
	for (int i = 1; i <= nr_bumpers; i++) {
		cin >> x >> y;
		grid[x][y] = i;
		cin >> bumpers[i].point_ >> bumpers[i].cost_;
	}
	int total_points = 0;
	while (cin >> x >> y >> direction >> lifetime) {
		int points = pinball(x, y, direction, lifetime);
		total_points += points;
		cout << points << endl;
	}
	cout << total_points << endl;
	return 0;
}

