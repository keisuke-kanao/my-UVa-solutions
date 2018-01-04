
/*
	UVa 11581 - Grid Successors

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11581_Grid_Successors.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int nr_cells = 3;

bool f(char (*pcc)[nr_cells + 1], char (*pnc)[nr_cells + 1])
{
	bool result = true;
	for (int i = 0; i < nr_cells; i++) {
		for (int j = 0; j < nr_cells; j++) {
			int s = 0;
			if (j)
				s += pcc[i][j - 1];
			if (j < nr_cells - 1)
				s += pcc[i][j + 1];
			if (i)
				s += pcc[i - 1][j];
			if (i < nr_cells - 1)
				s += pcc[i + 1][j];
			pnc[i][j] = s & 1;
#ifdef DEBUG
			putchar('0' + pnc[i][j]);
#endif
			if (pnc[i][j] != pcc[i][j])
				result = false;
		}
#ifdef DEBUG
		putchar('\n');
#endif
	}
#ifdef DEBUG
	putchar('\n');
#endif
	return result;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		char cells[nr_cells][nr_cells + 1], ncells[nr_cells][nr_cells + 1];
		for (int i = 0; i < nr_cells; i++)
			scanf("%s", cells[i]);
		for (int i = 0; i < nr_cells; i++)
			for (int j = 0; j < nr_cells; j++)
				cells[i][j] -= '0';
		char (*pcc)[nr_cells + 1] = cells, (*pnc)[nr_cells + 1] = ncells;
		int i;
		for (i = 0; ; i++) {
			if (f(pcc, pnc))
				break;
			swap(pcc, pnc);
		}
		printf("%d\n", i - 1);
	}
	return 0;
}

