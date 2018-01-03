
/*
	UVa 947 - Master Mind Helper

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_947_Master_Mind_Helper.cpp
*/

#include <cstdio>
#include <cstring>
using namespace std;

const int nr_digits_max = 5;
char guess[nr_digits_max + 1], code[nr_digits_max + 1];
int fn, sn;

void generate_code(int n, int ci, int& ctr)
{
	if (ci == n) {
		char s[nr_digits_max + 1], t[nr_digits_max + 1];
		memcpy(s, guess, n);
		memcpy(t, code, n);
		int fm = 0, sm = 0;
		for (int i = 0; i < n; i++)
			if (s[i] == t[i]) {
				s[i] = t[i] = '0';
				fm++;
			}
		for (int i = 0; i < n; i++)
			if (s[i] != '0')
				for (int j = 0; j < n; j++)
					if (s[i] == t[j]) {
						s[i] = t[j] = '0';
						sm++;
						break;
					}
		if (fn == fm && sn == sm)
			ctr++;
	}
	else {
		for (int i = 1; i <= 9; i++) {
			code[ci] = '0' + i;
			generate_code(n, ci + 1, ctr);
		}
	}
}

int main()
{
	int N;
	scanf("%d", &N);
	while (N--) {
		scanf("%s %d %d", guess, &fn, &sn);
		int ctr = 0;
		generate_code(strlen(guess), 0, ctr);
		printf("%d\n", ctr);
	}
	return 0;
}

