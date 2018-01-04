
/*
	UVa 11661 - Burger Time?

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11661_Burger_Time.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int l_max = 2000000;
char s[l_max + 1];

int main()
{
	while (true) {
		int l;
		scanf("%d", &l);
		if (!l)
			break;
		scanf("%s", s);
		int min_d = l;
		for (int i = 0, ri = -1, di = -1; i < l; i++) {
			if (s[i] == 'Z') {
				min_d = 0;
				break;
			}
			else if (s[i] == 'R') {
				ri = i;
				if (di != -1)
					min_d = min(min_d, ri - di);
			}
			else if (s[i] == 'D') {
				di = i;
				if (ri != -1)
					min_d = min(min_d, di - ri);
			}
		}
		printf("%d\n", min_d);
	}
	return 0;
}

