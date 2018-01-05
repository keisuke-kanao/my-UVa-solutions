
/*
	UVa 11074 - Draw Grid

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11074_Draw_Grid.cpp
*/

#include <cstdio>
#include <cstring>

const int s_max = 20, t_max = 20, n_max = 20;
char line[(s_max + t_max) * n_max + t_max + 1];

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		int s, t, n;
		scanf("%d %d %d", &s, &t, &n);
		if (!s && !t && !n)
			break;
		printf("Case %d:\n", case_nr);

		int l = (s + t) * n + t;
		line[l] = '\0';
		for (int i = 0; i < n; i++) {
			memset(line, '*', l);
			for (int j = 0; j < t; j++)
				puts(line);
			for (int j = t, k = 0; k < n; j += s + t, k++)
				memset(line + j, '.', s);
			for (int j = 0; j < s; j++)
				puts(line);
		}
		memset(line, '*', l);
		for (int j = 0; j < t; j++)
			puts(line);
		putchar('\n');
	}
	return 0;
}

