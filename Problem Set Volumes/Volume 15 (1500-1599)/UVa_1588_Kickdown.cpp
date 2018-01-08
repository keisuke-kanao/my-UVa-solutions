
/*
	UVa 1588 - Kickdown

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_1588_Kickdown.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

int stripe(const char* s, int n, const char* t, int m)
{
	int i, j, l;
	for (i = 0; i < n; i++) {
		l = min(m, n - i);
		for (j = 0; j < l; j++)
			if (s[i + j] == '2' && t[j] == '2')
				break;
		if (j == l)
			return (l == m) ? n : n + m - l;
	}
	return n + m;
}

int main()
{
	const int nr_chars_max = 100;
	char master[nr_chars_max + 1], driven[nr_chars_max + 1];
	while (scanf("%s", master) != EOF) {
		scanf("%s", driven);
		int n = strlen(master), m = strlen(driven);
		int s = 
		printf("%d\n", min(stripe(master, n, driven, m), stripe(driven, m, master, n)));
	}
	return 0;
}

