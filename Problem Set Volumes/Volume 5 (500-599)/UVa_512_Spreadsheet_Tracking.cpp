
/*
	UVa 512 - Spreadsheet Tracking

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_512_Spreadsheet_Tracking.cpp
*/

#include <algorithm>
#include <vector>
#include <utility>
#include <cstdio>
using namespace std;

#ifdef DEBUG
void print_sheet(int r, int c, const vector< vector< pair<int, int> > >& sheet)
{
	printf("%d %d\n", r, c);
	for (int i = 1; i <= r; i++)
		for (int j = 1; j <= c; j++)
			printf("(%2d,%2d)%c", sheet[i][j].first, sheet[i][j].second, ((j < c) ? ' ' : '\n'));
}
#endif

int main()
{
	for (int s = 1; ; s++) {
		int r, c, n;
		scanf("%d %d", &r, &c);
		if (!r)
			break;
		if (s > 1)
			putchar('\n');
		vector< vector< pair<int, int> > > sheet(r + 1, vector< pair<int, int> >(c + 1));
		for (int i = 1; i <= r; i++)
			for (int j = 1; j <= c; j++)
				sheet[i][j] = make_pair(i, j);
#ifdef DEBUG
		print_sheet(r, c, sheet);
#endif
		scanf("%d", &n);
		while (n--) {
			const int nr_chars_max = 2;
			char command[nr_chars_max + 1];
			scanf("%s", command);
			if (command[0] == 'E') { // "EX"
				int r1, c1, r2, c2;
				scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
				swap(sheet[r1][c1], sheet[r2][c2]);
			}
			else {
				const int A_max = 10;
				int A, x[A_max];
				scanf("%d", &A);
				for (int i = 0; i < A; i++)
					scanf("%d", &x[i]);
				sort(x, x + A);
				if (command[0] == 'D') {
					for (int i = 1, j = 1; i < A; i++, j++)
						x[i] -= j;
					if (command[1] == 'R') { // "DR"
						for (int i = 0; i < A; i++)
							sheet.erase(sheet.begin() + x[i]);
						r -= A;
					}
					else { // "DC"
						for (size_t i = 1, e = sheet.size(); i < e; i++) {
							vector< pair<int, int> >& row = sheet[i];
							for (int j = 0; j < A; j++)
								row.erase(row.begin() + x[j]);
						}
						c -= A;
					}
				}
				else {
					for (int i = 1, j = 1; i < A; i++, j++)
						x[i] += j;
					if (command[1] == 'R') { // "IR"
						for (int i = 0; i < A; i++)
							sheet.insert(sheet.begin() + x[i], vector< pair<int, int> >(c + 1));
						r += A;
					}
					else { // "IC"
						for (size_t i = 1, e = sheet.size(); i < e; i++) {
							vector< pair<int, int> >& row = sheet[i];
							for (int j = 0; j < A; j++)
								row.insert(row.begin() + x[j], pair<int, int>());
						}
						c += A;
					}
				}
			}
#ifdef DEBUG
			print_sheet(r, c, sheet);
#endif
		}
		printf("Spreadsheet #%d\n", s);
		scanf("%d", &n);
		while (n--) {
			int or_, oc;
			scanf("%d %d", &or_, &oc);
			pair<int, int> op = make_pair(or_, oc);
			int i, j;
			for (i = 1; i <= r; i++) {
				for (j = 1; j <= c; j++)
					if (sheet[i][j] == op)
						break;
				if (j <= c)
					break;
			}
			if (i <= r && j <= c)
				printf("Cell data in (%d,%d) moved to (%d,%d)\n", or_, oc, i, j);
			else
				printf("Cell data in (%d,%d) GONE\n", or_, oc);
		}
	}
	return 0;
}

