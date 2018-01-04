
/*
	UVa 12403 - Save Setu

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_12403_Save_Setu.cpp
*/

#include <cstdio>

int main()
{
	const int nr_chars_max = 16;
	char op[nr_chars_max];
	int t, k;
	scanf("%d", &t);
	int amount = 0;
	while (t--) {
		scanf("%s", op);
		if (op[0] == 'd') {
			scanf("%d", &k);
			amount += k;
		}
		else
			printf("%d\n", amount);
	}
	return 0;
}

