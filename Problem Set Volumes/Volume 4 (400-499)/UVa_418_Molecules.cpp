
/*
	UVa 418 - Molecules

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_418_Molecules.cpp

	from ACM East Central Regionals - 1995, Problem G
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_EastCen/1995/index.html)
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int nr_permutations = 24, nr_chains = 4, nr_elements = 12;

char molecules[nr_chains][nr_elements + 1];

const int orders[nr_permutations][nr_chains] = {
	{0, 1, 2, 3}, {0, 1, 3, 2}, {0, 2, 1, 3}, {0, 2, 3, 1},
	{0, 3, 1, 2}, {0, 3, 2, 1}, {1, 0, 2, 3}, {1, 0, 3, 2},
	{1, 2, 0, 3}, {1, 2, 3, 0}, {1, 3, 0, 2}, {1, 3, 2, 0},
	{2, 0, 1, 3}, {2, 0, 3, 1}, {2, 1, 0, 3}, {2, 1, 3, 0},
	{2, 3, 0, 1}, {2, 3, 1, 0}, {3, 0, 1, 2}, {3, 0, 2, 1},
	{3, 1, 0, 2}, {3, 1, 2, 0}, {3, 2, 0, 1}, {3, 2, 1, 0}
};

int main()
{
	while (true) {
		scanf("%s", molecules[0]);
		if (molecules[0][0] == 'Q')
			break;
		for (int i = 1; i < nr_chains; i++)
			scanf("%s", molecules[i]);
		int area = 0;
		for (int p = 0; p < nr_permutations; p++) {
			const char *vertical_left = molecules[orders[p][0]], *horizontal_up = molecules[orders[p][1]],
				*vertical_right = molecules[orders[p][2]], *horizontal_down = molecules[orders[p][3]];
			for (int i = 1; i < nr_elements - 1; i++)
				for (int j = 1; j < nr_elements - 1; j++) {
					if (vertical_left[i] != horizontal_up[j])
						continue;
					for (int jj = j + 2; jj < nr_elements - 1; jj++)
						for (int k = 1; k < nr_elements - 1; k++) {
							if (horizontal_up[jj] != vertical_right[k])
								continue;
							for (int ii = i + 2; ii < nr_elements - 1; ii++)
								for (int l = 1; l < nr_elements - 1; l++) {
									if (vertical_left[ii] != horizontal_down[l])
										continue;
									int kk = k + ii - i, ll = l + jj - j;
									if (kk > 0 && kk < nr_elements - 1 && ll > 0 && ll < nr_elements - 1 &&
										vertical_right[kk] == horizontal_down[ll]) {
										area = max(area, (ii - i - 1) * (jj - j - 1));
									}
								}
						}
				}
		}
		printf("%d\n", area);
	}
	return 0;
}

