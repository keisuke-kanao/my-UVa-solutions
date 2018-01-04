
/*
	UVa 403 - Postscript

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_403_Postscript.cpp

	from ACM  South Central Regionals - 1995, Problem #4
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_SouthCen/1995/index.html)
*/

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

const int nr_letters = 26, nr_rows = 60, nr_columns = 60, nr_c5_rows = 5, nr_c5_columns = 6;

const char* c5_letters[nr_letters][nr_c5_rows] = {
// A B C D E F G H I
	{".***..", "*...*.", "*****.", "*...*.", "*...*."},
	{"****..", "*...*.", "****..", "*...*.", "****.."},
	{".****.", "*...*.", "*.....", "*.....", ".****."},
	{"****..", "*...*.", "*...*.", "*...*.", "****.."},
	{"*****.", "*.....", "***...", "*.....", "*****."},
	{"*****.", "*.....", "***...", "*.....", "*....."},
	{".****.", "*.....", "*..**.", "*...*.", ".***.."},
	{"*...*.", "*...*.", "*****.", "*...*.", "*...*."},
	{"*****.", "..*...", "..*...", "..*...", "*****."},
// J K L M N O P Q R
	{"..***.", "...*..", "...*..", "*..*..", ".**..."},
	{"*...*.", "*..*..", "***...", "*..*..", "*...*."},
	{"*.....", "*.....", "*.....", "*.....", "*****."},
	{"*...*.", "**.**.", "*.*.*.", "*...*.", "*...*."},
	{"*...*.", "**..*.", "*.*.*.", "*..**.", "*...*."},
	{".***..", "*...*.", "*...*.", "*...*.", ".***.."},
	{"****..", "*...*.", "****..", "*.....", "*....."},
	{".***..", "*...*.", "*...*.", "*..**.", ".****."},
	{"****..", "*...*.", "****..", "*..*..", "*...*."},
// S T U V W X Y Z
	{".****.", "*.....", ".***..", "....*.", "****.."},
	{"*****.", "*.*.*.", "..*...", "..*...", ".***.."},
	{"*...*.", "*...*.", "*...*.", "*...*.", ".***.."},
	{"*...*.", "*...*.", ".*.*..", ".*.*..", "..*..."},
	{"*...*.", "*...*.", "*.*.*.", "**.**.", "*...*."},
	{"*...*.", ".*.*..", "..*...", ".*.*..", "*...*."},
	{"*...*.", ".*.*..", "..*...", "..*...", "..*..."},
	{"*****.", "...*..", "..*...", ".*....", "*****."}
};

char grid[nr_rows][nr_columns + 1];

void init_grid()
{
	for (int r = 0; r < nr_rows; r++)
		for (int c = 0; c < nr_columns; c++)
			grid[r][c] = '.';
}

void print_c5_char(int rs, int cs, char s)
{
	const char** letter = c5_letters[s - 'A'];
	for (int r = rs, re = min(rs + nr_c5_rows, nr_rows); r < re; r++) {
		for (int c = cs, ce = min(cs + nr_c5_columns, nr_columns); c < ce; c++)
			if (c >= 0 && letter[r - rs][c - cs] != '.')
				grid[r][c] = letter[r - rs][c - cs];
	}
}

void print_string(bool c5, int rs, int cs, const char* s)
{
	for (int c = cs; c < nr_columns && *s != '|'; c += ((c5) ? nr_c5_columns : 1), s++)
		if (*s != ' ') {
			if (c5)
				print_c5_char(rs, c, *s);
			else if (c >= 0)
				grid[rs][c] = *s;
		}
}

int main()
{
	init_grid();
	string line;
	while (getline(cin, line)) {
		istringstream iss(line);
		string command, font;
		bool c5 = false;
		int R, C, length;
		const char* S;
		iss >> command;
		if (command[1] != 'E') {
			iss >> font >> R;
			if (font[1] == '5')
				c5 = true;
			R--;
		}
		if (command[1] == 'P') {
			iss >> C;
			C--;
		}
		if (command[1] != 'E') {
			S = line.c_str() + line.find('|') + 1;
			length = line.c_str() + line.rfind('|') - S;
			if (c5)
				length *= nr_c5_columns;
		}
		switch (command[1]) {
		case 'P':
			print_string(c5, R, C, S);
			break;
		case 'L':
			print_string(c5, R, 0, S);
			break;
		case 'R':
			print_string(c5, R, 60 - length, S);
			break;
		case 'C':
			C = nr_columns - length;
			if (C > 0)
				C++;
			print_string(c5, R, C / 2, S);
			break;
		case 'E':
			for (int r = 0; r < nr_rows; r++)
				cout << grid[r] << endl;
			cout << "\n------------------------------------------------------------\n\n";
			init_grid();
			break;
		}
	}
	return 0;
}

