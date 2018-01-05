
/*
	UVa 10894 - Save Hridoy

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10894_Save_Hridoy.cpp
*/

#include <cstdio>

const int hbanner_rows = 5, hbanner_columns = 61, vbanner_rows = 61, vbanner_columns = 5, N_max = 50;

char hbanner[hbanner_rows][hbanner_columns + 1] = {
	"*****..***..*...*.*****...*...*.*****.*****.***...*****.*...*",
	"*.....*...*.*...*.*.......*...*.*...*...*...*..*..*...*..*.*.",
	"*****.*****.*...*.***.....*****.*****...*...*...*.*...*...*..",
	"....*.*...*..*.*..*.......*...*.*.*.....*...*..*..*...*...*..",
	"*****.*...*...*...*****...*...*.*..**.*****.***...*****...*.."
};

char vbanner[vbanner_rows][vbanner_columns + 1] = {
	"*****",
	"*....",
	"*****",
	"....*",
	"*****",
	".....",
	".***.",
	"*...*",
	"*****",
	"*...*",
	"*...*",
	".....",
	"*...*",
	"*...*",
	"*...*",
	".*.*.",
	"..*..",
	".....",
	"*****",
	"*....",
	"***..",
	"*....",
	"*****",
	".....",
	".....",
	".....",
	"*...*",
	"*...*",
	"*****",
	"*...*",
	"*...*",
	".....",
	"*****",
	"*...*",
	"*****",
	"*.*..",
	"*..**",
	".....",
	"*****",
	"..*..",
	"..*..",
	"..*..",
	"*****",
	".....",
	"***..",
	"*..*.",
	"*...*",
	"*..*.",
	"***..",
	".....",
	"*****",
	"*...*",
	"*...*",
	"*...*",
	"*****",
	".....",
	"*...*",
	".*.*.",
	"..*..",
	"..*..",
	"..*.."
};

int main()
{
	char buff[hbanner_columns * N_max + 1];
	while (true) {
		int N;
		scanf("%d", &N);
		if (!N)
			break;
		if (N > 0) {
			for (int si = 0; si < hbanner_rows; si++) {
				int dj = 0;
				for (int sj = 0; sj < hbanner_columns; sj++)
					for (int n = 0; n < N; n++, dj++)
						buff[dj] = hbanner[si][sj];
				buff[dj] = '\0';
				for (int n = 0; n < N; n++)
					printf("%s\n", buff);
			}
		}
		else {
			int L = -N;
			for (int si = 0; si < vbanner_rows; si++) {
				int dj = 0;
				for (int sj = 0; sj < vbanner_columns; sj++)
					for (int n = 0; n < L; n++, dj++)
						buff[dj] = vbanner[si][sj];
				buff[dj] = '\0';
				for (int n = 0; n < L; n++)
					printf("%s\n", buff);
			}
		}
		printf("\n\n");
	}
	return 0;
}

