
/*
	UVa 12210 - A Match Making Problem

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12210_A_Match_Making_Problem.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int nr_bachelors_max = 10000;
int bachelors[nr_bachelors_max];

int main()
{
	for (int cn = 1; ; cn++) {
		int i, b, s;
		scanf("%d %d", &b, &s);
		if (!b && !s)
			break;
		if (b > s) {
			for (i = 0; i < b; i++)
				scanf("%d", &bachelors[i]);
			for (i = 0; i < s; i++)
				scanf("%*d");
			sort(bachelors, bachelors + b);
			printf("Case %d: %d %d\n", cn, b - s, bachelors[0]);
		}
		else {
			for (i = 0; i < b; i++)
				scanf("%*d");
			for (i = 0; i < s; i++)
				scanf("%*d");
			printf("Case %d: 0\n", cn);
		}
	}
	return 0;
}

