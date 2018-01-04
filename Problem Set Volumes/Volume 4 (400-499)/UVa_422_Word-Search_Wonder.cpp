
/*
	UVa 422 - Word-Search Wonder

	To build using Visucal Studio 2008:
		cl -EHsc UVa_422_Word-Search_Wonder.cpp

	from ACM  East Central Regionals 1996
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_EastCen/1996/solutions/index.html)

	This problem is similar to UVa 10010 - Where's Waldorf?.
*/

#include <cstdio>
#include <cstring>

const int nr_letters_max = 100;
char grid[nr_letters_max][nr_letters_max];

bool match_string(int n, int line, int column, int line_dir, int column_dir, const char* s, int length)
{
	for (int i = 0; i < length; i++, line += line_dir, column += column_dir) {
		if (line_dir > 0 && line >= n || line_dir < 0 && n < 0) // out of a line
			return false;
		if (column_dir > 0 && column >= n || column_dir < 0 && column < 0) // out of a column
			return false;
		if (s[i] != grid[line][column])
			return false;
	}
	return true;
}

bool find_string(int n, const char* s, int length, int& fline, int& fcolumn, int& lline, int& lcolumn)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (s[0] != grid[i][j])
				continue;
			for (int line_dir = -1; line_dir <= 1; line_dir++)
				for (int column_dir = -1; column_dir <= 1; column_dir++) {
					if (!line_dir && !column_dir)
						continue;
					if (match_string(n, i, j, line_dir, column_dir, s, length)) {
						fline = i + 1; fcolumn = j + 1;
						lline = fline;
						if (line_dir)
							lline += line_dir * (length - 1);
						lcolumn = fcolumn;
						if (column_dir)
							lcolumn += column_dir * (length - 1);
						return true;
					}
				}
		}
	return false;
}

int main()
{
	int l;
	scanf("%d", &l);
	getchar();
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < l; j++)
			scanf("%c", &grid[i][j]);
		getchar();
	}
	while (true) {
		char s[nr_letters_max + 1];
		scanf("%s", s);
		if (s[0] == '0')
			break;
		int fline, fcolumn, lline, lcolumn;
		if (find_string(l, s, strlen(s), fline, fcolumn, lline, lcolumn))
			printf("%d,%d %d,%d\n", fline, fcolumn, lline, lcolumn);
		else
			printf("Not found\n");
	}
	return 0;
}

