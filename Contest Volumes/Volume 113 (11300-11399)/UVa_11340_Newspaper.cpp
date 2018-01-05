
/*
	UVa 11340 - Newspaper

	To build using Visual Studio 2008:
		cl -EHsc UVa_11340_Newspaper.cpp
*/

#include <cstdio>
#include <cstring>

int main()
{
	const int nr_cost_chars = 256;
	int values[nr_cost_chars];
	const int nr_chars_max = 10000;
	char s[nr_chars_max + 1];
	int t;
	scanf("%d", &t);
	getchar();
	while (t--) {
		int k;
		scanf("%d", &k);
		getchar();
		memset(values, 0, sizeof(values));
		while (k--) {
			char c;
			int v;
			scanf("%c %d", &c, &v);
			getchar();
			values[c + 128] = v;
		}
		int m;
		scanf("%d", &m);
		getchar();
		unsigned long long amount = 0;
		while (m--) {
			gets(s);
			for (const char* p = s; *p; p++)
				amount += values[*p + 128];
		}
		printf("%llu.%02llu$\n", amount / 100, amount % 100);
	}
	return 0;
}

