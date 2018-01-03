
/*
	UVa 585 - Triangles

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_585_Triangles.cpp

	from ACM Western and Southwestern European Regionals 1997
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_EU_SWERC/1997/index.html)
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int n_max = 100;
char triangles[n_max][n_max * 2];

int largest_triangle(int n, int ti, int tj)
{
	int nr = 0;
	for (int k = 1; ti < n; k++, ti++) {
		if (tj - k < ti + 1 || tj + k > 2 * n - ti - 3)
			return nr;
		for (int j = tj - k; j <= tj + k; j++)
			if (triangles[ti][j] != '-')
				return nr;
		nr += 2 * k + 1;
	}
	return nr;
}

int largest_inverted_triangle(int n, int ti, int tj)
{
	int nr = 0;
	for (int k = 1; ti >= 0; k++, ti--) {
		if (tj - k < ti || tj + k > 2 * n - ti - 2)
			return nr;
		for (int j = tj - k; j <= tj + k; j++)
			if (triangles[ti][j] != '-')
				return nr;
		nr += 2 * k + 1;
	}
	return nr;
}

int main()
{
	for (int nr = 1; ; nr++) {
		int n;
		scanf("%d", &n);
		getchar(); // skip '\n'
		if (!n)
			break;
		for (int i = 0; i < n; i++)
			gets(triangles[i]);
		int largest = 0;
		for (int i = 0; i < n; i++)
			for (int j = i + 1, jh = 2 * n - i - 1; j < jh; j += 2)
				if (triangles[i][j] == '-')
					largest = max(largest, 1 + largest_triangle(n, i + 1, j));
		for (int i = n - 1; i >= 0; i--)
			for (int j = i, jh = 2 * n - i - 1; j < jh; j += 2)
				if (triangles[i][j] == '-')
					largest = max(largest, 1 + largest_inverted_triangle(n, i - 1, j));
		printf("Triangle #%d\nThe largest triangle area is %d.\n\n", nr, largest);
	}
	return 0;
}

