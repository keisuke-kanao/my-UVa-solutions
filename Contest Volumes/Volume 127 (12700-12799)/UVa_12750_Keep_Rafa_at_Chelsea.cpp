
/*
	UVa 12750 - Keep Rafa at Chelsea

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12750_Keep_Rafa_at_Chelsea.cpp
*/

#include <cstdio>

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int n;
		scanf("%d", &n);
		int sack = 0;
		for (int i = 1, not_win = 0; i <= n; i++) {
			if (sack)
				scanf("%*s");
			else {
				char s[2];
				scanf("%s", s);
				if (s[0] == 'W')
					not_win = 0;
				else if (++not_win == 3)
					sack = i;
			}
		}
		if (sack)
			printf("Case %d: %d\n", t, sack);
		else
			printf("Case %d: Yay! Mighty Rafa persists!\n", t);
	}
	return 0;
}

