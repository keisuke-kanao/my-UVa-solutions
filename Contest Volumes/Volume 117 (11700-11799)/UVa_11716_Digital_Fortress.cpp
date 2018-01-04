
/*
	UVa 11716 - Digital Fortress

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11716_Digital_Fortress.cpp
*/

#include <cstdio>
#include <cstring>
#include <cmath>

const int nr_rows_max = 100, nr_columns_max = 100;
char grid[nr_rows_max][nr_columns_max];
char text[nr_rows_max * nr_columns_max + 1];

int main()
{
	int t;
	scanf("%d", &t);
	getchar();
	while (t--) {
		gets(text);
		int length = strlen(text);
		int nr_rows = static_cast<int>(sqrt(static_cast<double>(length)));
		if (nr_rows * nr_rows != length)
			printf("INVALID\n");
		else {
			const char* p = text;
			for (int i = 0; i < nr_rows; i++)
				for (int j = 0; j < nr_rows; j++)
					grid[i][j] = *p++;
			for (int j = 0; j < nr_rows; j++)
				for (int i = 0; i < nr_rows; i++)
					putchar(grid[i][j]);
			putchar('\n');
		}
	}
	return 0;
}

