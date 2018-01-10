
/*
	UVa 196 - Spreadsheet

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_196_Spreadsheet.cpp

	from ACM Southwestern European Regional Contest 1995 Problem F
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_EU_SWERC/1995/index.html)
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cstdlib>
#include <cctype>
using namespace std;

void topologica_sort(int n, vector<int>& in_degrees, const vector< vector<int> >& adjacency_list, vector<int>& cells)
{
	queue<int> q;
	for (int i = 0; i < n; i++)
		if (!in_degrees[i])
			q.push(i);
	while (!q.empty()) {
		int i = q.front(); q.pop();
		const vector<int>& al = adjacency_list[i];
		for (size_t j = 0, e = al.size(); j < e; j++) {
			int k = al[j];
			cells[k] += cells[i];
			if (!--in_degrees[k])
				q.push(k);
		}
	}
}

int main()
{
	const int nr_uppers = 'Z' - 'A' + 1;
	int nr_sheets;
	cin >> nr_sheets;
	while (nr_sheets--) {
		int nr_columns, nr_rows;
		cin >> nr_columns >> nr_rows;
		int n = nr_rows * nr_columns;
		vector<int> cells(n, 0);
		vector<int> in_degrees(n, 0);
		vector< vector<int> > adjacency_list(n, vector<int>());
		for (int i = 0; i < nr_rows; i++)
			for (int j = 0; j < nr_columns; j++) {
				int k = i * nr_columns + j;
				string s;
				cin >> s;
				const char* p = s.c_str();
				if (*p == '=') { // formula
					for (p++; *p; ) {
						int c = 0;
						for ( ; isupper(*p); p++) { // get a column number
							c *= nr_uppers;
							c += *p - 'A' + 1;
						}
						int r = 0;
						for ( ; isdigit(*p); p++) { // get a row number
							r *= 10;
							r += *p - '0';
						}
						in_degrees[k]++;
						adjacency_list[(--r) * nr_columns + (--c)].push_back(k);
						if (*p) // '+'
							p++;
					}
				}
				else // number
					cells[k] = atoi(p);
			}
		topologica_sort(n, in_degrees, adjacency_list, cells);
		for (int i = 0; i < nr_rows; i++)
			for (int j = 0; j < nr_columns; j++) {
				int k = i * nr_columns + j;
				cout << cells[k] << ((j == nr_columns - 1) ? '\n' : ' ');
			}
	}
	return 0;
}

