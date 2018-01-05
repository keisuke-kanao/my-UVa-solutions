
/*
	UVa 10500 - Robot maps

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10500_Robot_maps.cpp
*/

#include <iostream>
using namespace std;

const int n_max = 10, m_max = 10;
char map[n_max + 1][m_max + 1], robot_map[n_max +1][m_max + 1];
bool visited[n_max + 1][m_max + 1];

int dfs(int n, int m, int px, int py)
{
	const int dirs[][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
	const size_t nr_dirs = sizeof(dirs) / sizeof(dirs[0]);

	visited[px][py] = true;
	for (size_t i = 0; i < nr_dirs; i++) {
		int x = px + dirs[i][0], y = py + dirs[i][1];
		if (x >= 1 && x <= n && y >= 1 && y <= m)
			robot_map[x][y] = map[x][y];
	}
	int nr_visited = 0;
	for (size_t i = 0; i < nr_dirs; i++) {
		int x = px + dirs[i][0], y = py + dirs[i][1];
		if (x >= 1 && x <= n && y >= 1 && y <= m && map[x][y] == '0' && !visited[x][y]) {
			nr_visited = 1 + dfs(n, m, x, y);
			break;
		}
	}
	return nr_visited;
}

int main()
{
	while (true) {
		int n, m;
		cin >> n >> m;
		if (!n && !m)
			break;
		int x_ini, y_ini;
		cin >> x_ini >> y_ini;
		for (int x = 1; x <= n; x++)
			for (int y = 1; y <= m; y++) {
				visited[x][y] = false;
				robot_map[x][y] = '?';
				cin >> map[x][y];
			}
		robot_map[x_ini][y_ini] = '0';
		int nr_movements = dfs(n, m, x_ini, y_ini);
		cout << endl;
		for (int y = 1; y <= m; y++)
			cout << "|---";
		cout << "|\n";
		for (int x = 1; x <= n; x++) {
			for (int y = 1; y <= m; y++)
				cout << "| " << robot_map[x][y] << ' ';
			cout << "|\n";
			for (int y = 1; y <= m; y++)
				cout << "|---";
			cout << "|\n";
		}
		cout << "\nNUMBER OF MOVEMENTS: " << nr_movements << endl;
	}
	return 0;
}

