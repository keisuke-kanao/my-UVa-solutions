
/*
	UVa 10377 - Maze Traversal

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10377_Maze_Traversal.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
	string line;
	istringstream iss;
	getline(cin, line);
	iss.str(line);
	int nr_cases;
	iss >> nr_cases;
	iss.clear();
	while (nr_cases--) {
		getline(cin, line); // skip a blank line
		getline(cin, line);
		iss.str(line);
		int nr_rows, nr_columns;
		iss >> nr_rows >> nr_columns;
		iss.clear();
		vector< vector<char> > maze(nr_rows, vector<char>(nr_columns));
		for (int i = 0; i < nr_rows; i++) {
			getline(cin, line);
			for (int j = 0; j < nr_columns; j++)
				maze[i][j] = line[j];
		}
		getline(cin, line);
		iss.str(line);
		int r, c;
		iss >> r >> c;
		r--; c--;
		iss.clear();
		char dir = 'N';
		bool quit = false;
		while (!quit) {
			getline(cin, line);
			for (int i = 0; i < line.length() && !quit; i++) {
				switch (line[i]) {
				case 'R':
					switch (dir) {
					case 'N':
						dir = 'E'; break;
					case 'S':
						dir = 'W'; break;
					case 'E':
						dir = 'S'; break;
					case 'W':
						dir = 'N'; break;
					}
					break;
				case 'L':
					switch (dir) {
					case 'N':
						dir = 'W'; break;
					case 'S':
						dir = 'E'; break;
					case 'E':
						dir = 'N'; break;
					case 'W':
						dir = 'S'; break;
					}
					break;
				case 'F':
					switch (dir) {
					case 'N':
						if (r && maze[r - 1][c] == ' ')
							r--;
						break;
					case 'S':
						if (r < nr_rows - 1 && maze[r + 1][c] == ' ')
							r++;
						break;
					case 'E':
						if (c < nr_columns - 1 && maze[r][c + 1] == ' ')
							c++;
						break;
					case 'W':
						if (c && maze[r][c - 1] == ' ')
							c--;
						break;
					}
					break;
				case 'Q':
					quit = true; break;
				default:
					break;
				}
			}
		}
		cout << r + 1 << ' ' << c + 1 << ' ' << dir << endl;
		if (nr_cases)
			cout << endl;
	}
	return 0;
}

