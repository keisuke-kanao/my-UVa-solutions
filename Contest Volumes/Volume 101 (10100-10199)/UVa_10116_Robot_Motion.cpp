
/*
	UVa 10116 - Robot Motion

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10116_Robot_Motion.cpp
*/

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	while (true) {
		int nr_rows, nr_columns, r = 0, c;
		cin >> nr_rows >> nr_columns >> c;
		if (!nr_rows && !nr_columns && !c)
			break;
		c--;
		vector< vector<char> > grid(nr_rows, vector<char>(nr_columns));
		for (int i = 0; i < nr_rows; i++)
			for (int j = 0; j < nr_columns; j++)
				cin >> grid[i][j];
		bool exit = false;
		int nr_steps = 1, nr_loop_steps = 0;
		do {
			switch (grid[r][c]) {
			case 'N':
				if (!r)
					exit = true;
				else
					grid[r--][c] = nr_steps++;
				break;
			case 'S':
				if (r < nr_rows - 1)
					grid[r++][c] = nr_steps++;
				else
					exit = true;
				break;
			case 'E':
				if (c < nr_columns - 1)
					grid[r][c++] = nr_steps++;
				else
					exit = true;
				break;
			case 'W':
				if (!c)
					exit = true;
				else
					grid[r][c--] = nr_steps++;
				break;
			default:
				nr_loop_steps = nr_steps - grid[r][c];
				nr_steps = grid[r][c] - 1;
				exit = true;
				break;
			}
		} while (!exit);
		if (nr_loop_steps)
			cout << nr_steps << " step(s) before a loop of " << nr_loop_steps << " step(s)\n";
		else
			cout << nr_steps << " step(s) to exit\n";
	}
	return 0;
}

