
/*
	UVa 1261 - String Popping

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1261_String_Popping.cpp

*/

#include <set>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_chars_max = 25;
set< pair<int, int> > visited;

bool string_popping(int n, int bs)
{
#ifdef DEBUG
	printf("%d: ", n);
	if (n) {
		for (int b = 1 << (n - 1); b; b >>=1)
			putchar((bs & b) ? 'b' : 'a');
	}
	putchar('\n');
#endif
	if (!n)
		return true;
	if (n == 1)
		return false;
	int m = n, b = 1 << (n - 1), pb = bs & b, ctr = 1;
	for (m--, b >>= 1; b; m--, b >>= 1) {
		int cb = bs & b;
		if (cb && pb || !cb && !pb) // consecutive same characters
			ctr++;
		else {
			if (ctr > 1) {
				int mask = (1 << m) - 1;
				int nbs = bs & mask | (bs >> ctr) & ~mask; // pop consecutive same characters
				pair<set< pair<int, int> >::iterator, bool> result = visited.insert(make_pair(n - ctr, nbs));
				if (result.second) {
					if (string_popping(n - ctr, nbs))
						return true;
				}
			}
			pb = cb, ctr = 1;
		}
	}
	if (ctr > 1) {
		int nbs = bs >> ctr;
		pair<set< pair<int, int> >::iterator, bool> result = visited.insert(make_pair(n - ctr, nbs));
		if (result.second) {
			if (string_popping(n - ctr, nbs))
				return true;
		}
	}
	return false;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		char s[nr_chars_max + 1];
		scanf("%s", s);
		int n = strlen(s);
		int bs = 0;
		for (int i = n - 1, b = 1; i >= 0; i--, b <<= 1)
			if (s[i] == 'b')
				bs |= b;
		visited.clear();
		visited.insert(make_pair(n, bs));
		bool result = string_popping(n, bs);
#ifdef DEBUG
		printf("visited: %u\n", visited.size());
#endif
		puts((result) ? "1" : "0");
	}
	return 0;
}

