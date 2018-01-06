
/*
	UVa 10063 - Knuth's Permutation

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10063_Knuths_Permutation.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_chars_max = 10;

void knuths_permutation(int n, int i, const char* s, char* t)
{
	if (i == n) {
		t[n] = '\0';
		printf("%s\n", t);
	}
	else {
		char u[nr_chars_max + 1];
		u[0] = s[i];
		memcpy(&u[1], t, i);
		knuths_permutation(n, i + 1, s, u);
		for (int j = 0; j < i; j++) {
			swap(u[j], u[j + 1]);
			knuths_permutation(n, i + 1, s, u);
		}
	}
}

int main()
{
	bool printed = false;
	char s[nr_chars_max + 1], t[nr_chars_max + 1];
	while (scanf("%s", s) != EOF) {
		if (printed)
			putchar('\n');
		else
			printed = true;
		knuths_permutation(strlen(s), 0, s, t);
	}
	return 0;
}

