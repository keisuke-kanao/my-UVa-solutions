
/*
	UVa 11576 - Scrolling Sign

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11576_Scrolling_Sign.cpp

	from Waterloo local contest, 8 February, 2009, Problem E
		(http://acm.student.cs.uwaterloo.ca/~acm00/090208/data/)
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

int compare_string(int k , const char* s, const char* t)
{
	for (int ti = k - 1; ti >= 0; ti--) {
		int i, j;
		for (i = ti, j = k - 1; i >= 0; i--, j--)
			if (t[i] != s[j])
				break;
		if (i < 0)
			return ti + 1; // number of chars martched
	}
	return 0;
}

int main()
{
	int n;
	scanf("%d", &n);
	while (n--) {
		int k, w;
		scanf("%d %d", &k, &w);
		const int k_max = 100;
		char s[k_max + 1], t[k_max + 1];
		scanf("%s", s);
		int nr = strlen(s);
		char *ps = s, *pt = t;
		while (--w) {
			scanf("%s", pt);
			int nr_matched = compare_string(k , ps, pt);
			nr += k - nr_matched;
			swap(ps, pt);
		}
		printf("%d\n", nr);
	}
	return 0;
}

