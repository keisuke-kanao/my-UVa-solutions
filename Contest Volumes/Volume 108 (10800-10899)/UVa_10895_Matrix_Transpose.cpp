
/*
	UVa 10895 - Matrix Transpose

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10895_Matrix_Transpose.cpp
*/

#include <cstdio>
#include <algorithm>
using namespace std;

const int nr_non_zero_elements_max = 1000;

struct element {
	int row_;
	int column_;
	int value_;
	bool operator<(const element& e) const {
		if (row_ < e.row_)
			return true;
		else if (row_ > e.row_)
			return false;
		else
			return column_ < e.column_;
	}
} elements[nr_non_zero_elements_max];

int main()
{
	int m, n;
	while (scanf("%d %d", &m, &n) != EOF) {
		int r, c, nr_elements = 0;
		for (r = 1; r <= m; r++) {
			int nc;
			scanf("%d", &nc);
			for (c = 0; c < nc; c++) {
				elements[nr_elements + c].column_ = r;
				scanf("%d", &elements[nr_elements + c].row_);
			}
			for (c = 0; c < nc; c++)
				scanf("%d", &elements[nr_elements + c].value_);
			nr_elements += c;
		}
		sort(elements, elements + nr_elements);
		printf("%d %d\n", n, m); 
		int cs = 0, ce = 0;
		for (r = 1; r <= n; r++) {
			for ( ; elements[ce].row_ == r; ce++)
				;
			int nc = ce - cs;
			printf("%d", nc);
			for (c = 0; c < nc; c++)
				printf(" %d", elements[cs + c].column_);
			putchar('\n');
			for (c = 0; c < nc; c++) {
				if (c)
					putchar(' ');
				printf("%d", elements[cs + c].value_);
			}
			putchar('\n');
			cs = ce;
		}
	}
	return 0;
}

