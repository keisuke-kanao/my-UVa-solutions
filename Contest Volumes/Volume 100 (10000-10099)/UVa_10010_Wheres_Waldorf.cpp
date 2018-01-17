
/*
	3.8.2 Where's Waldorf?
	PC/UVa IDs: 110302/10010, Popularity: B, Success rate: average Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10010_Wheres_Waldorf.cpp
*/

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

const int number_of_lines_max = 50;
const int number_of_columns_max = 50;

bool match_string(int lines, int columns, char grid[number_of_lines_max][number_of_columns_max],
	int line, int column, int line_dir, int column_dir, const string& s)
{
	for (int i = 0, length = s.length(); i < length; i++, line += line_dir, column += column_dir) {
		if (line_dir > 0 && line >= lines || line_dir < 0 && lines < 0) // out of a line
			return false;
		if (column_dir > 0 && column >= columns || column_dir < 0 && column < 0) // out of a column
			return false;
		if (s[i] != grid[line][column])
			return false;
	}
	return true;
}

bool find_string(int lines, int columns, char grid[number_of_lines_max][number_of_columns_max],
	const string& s, int& line, int& column)
{
	line = column = -1;
	for (int i = 0; i < lines; i++)
		for (int j = 0; j < columns; j++) {
			if (s[0] != grid[i][j])
				continue;
			for (int line_dir = -1; line_dir <= 1; line_dir++)
				for (int column_dir = -1; column_dir <= 1; column_dir++) {
					if (!line_dir && !column_dir)
						continue;
					if (match_string(lines, columns, grid, i, j, line_dir, column_dir, s)) {
						line = i; column = j;
						return true;
					}
				}
		}
	return false;
}

int main(int /* argc */, char** /* argv */)
{
	string line;
	istringstream iss;

	// read the number of cases
	getline(cin, line);
	iss.str(line);
	int cases;
	iss >> cases;
	iss.clear();
	while (cases) {
		getline(cin, line); // skip a blank line

		// read a line containing the number of lines (m) and the number of columns (n)
		getline(cin, line);
		iss.str(line);
		int m, n;
		iss >> m >> n;
		iss.clear();

		// read a grid of letters
		char grid[number_of_lines_max][number_of_columns_max];
		for (int i = 0; i < m; i++) {
			getline(cin, line);
			iss.str(line);
			for (int j = 0; j < n; j++) {
				char c;
				iss >> c;
				grid[i][j] = tolower(c);
			}
			iss.clear();
		}

		// read the number or words to search for
		getline(cin, line);
		iss.str(line);
		int k;
		iss >> k;
		iss.clear();

		// read each word, search it in the grid, and print its location
		for (int i = 0; i < k; i++) {
			getline(cin, line);
			transform(line.begin(), line.end(), line.begin(), (int(*)(int))tolower);
			int l, c;
			if (find_string(m, n, grid, line, l, c))
				cout << l + 1 << ' ' << c + 1 << endl;
		}
		if (--cases)
			cout << endl; // the output of two consecutive cases must be separated by a blank line
	}

	return 0;
}

