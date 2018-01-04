
/*
	UVa 337 - Interpreting Control Sequences

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_337_Interpreting_Control_Sequences.cpp

	from ACM North Central Regionals 1994
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_NorthCen/1994/index.html)
*/

#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
using namespace std;

int main()
{
	const int nr_rows = 10, nr_columns = 10;
	char terminal[nr_rows][nr_columns];
	for (int case_nr = 1; ; case_nr++) {
		memset(terminal, ' ', sizeof(terminal));
		int n;
		cin >> n;
		if (!n)
			break;
		string s;
		getline(cin, s); // skip '\n'
		int r = 0, c = 0;
		bool insert = false;
		while (n--) {
			getline(cin, s);
			for (const char* p = s.c_str(); *p; p++) {
				if (*p == '^') {
					if (isdigit(*++p)) { // Move the cursor to the row and column specified
						r = *p - '0'; c = *++p - '0';
					}
					else {
						switch (*p) {
						case 'b': // Move the cursor to the beginning of the current line; the cursor row does not change
							c = 0;
							break;
						case 'c': // Clear the entire screen; the cursor row and column do not change
							memset(terminal, ' ', sizeof(terminal));
							break;
						case 'd': // Move the cursor down one row if possible
							if (r < nr_rows - 1)
								r++;
							break;
						case 'e': // Erase characters to the right of, and including, the cursor column on the cursor's row
							for (int i = c; i < nr_columns; i++)
								terminal[r][c] = ' ';
							break;
						case 'h': // Move the cursor to row 0, column 0
							r = c = 0;
							break;
						case 'i': // Enter insert mode
							insert = true;
							break;
						case 'l': // Move the cursor left one column, if possible
							if (c)
								c--;
							break;
						case 'o': // Enter overwrite mode
							insert = false;
							break;
						case 'r': // Move the cursor right one column, if possible
							if (c < nr_columns - 1)
								c++;
							break;
						case 'u': // Move the cursor up one row, if possible
							if (r)
								r--;
							break;
						case '^': // Write a circumflex
							if (insert) {
								for (int i = nr_columns - 1; i >= c + 1; i--)
									terminal[r][i] = terminal[r][i - 1];
							}
							terminal[r][c] = '^';
							if (c < nr_columns - 1)
								c++;
							break;
						}
					}
				}
				else {
					if (insert) {
						for (int i = nr_columns - 1; i >= c + 1; i--)
							terminal[r][i] = terminal[r][i - 1];
					}
					terminal[r][c] = *p;
					if (c < nr_columns - 1)
						c++;
				}
			}
		}

		cout << "Case " << case_nr << endl;
		cout << "+----------+\n";
		for (r = 0; r < nr_rows; r++) {
			cout << '|';
			for (c = 0; c < nr_columns; c++)
				cout << terminal[r][c];
			cout << "|\n";
		}
		cout << "+----------+\n";
	}
	return 0;
}

