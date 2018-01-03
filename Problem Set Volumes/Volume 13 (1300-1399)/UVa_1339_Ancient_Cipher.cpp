
/*
	UVa 1339 - Ancient Cipher

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1339_Ancient_Cipher.cpp
*/

#include <functional>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_letters = 26, nr_chars_max = 100;

int main()
{
	char s[nr_chars_max + 1], t[nr_chars_max + 1];
	int sl[nr_letters], tl[nr_letters];
	while (scanf("%s", s) != EOF) {
		scanf("%s", t);
		memset(sl, 0, sizeof(sl));
		memset(tl, 0, sizeof(tl));
		for (const char* p = s; *p; p++)
			sl[*p - 'A']++;
		for (const char* p = t; *p; p++)
			tl[*p - 'A']++;
		sort(sl, sl + nr_letters, greater<int>());
		sort(tl, tl + nr_letters, greater<int>());
		bool yes = true;
		for (int i = 0; i < nr_letters && (sl[i] || tl[i]); i++)
			if (sl[i] != tl[i]) {
				yes = false;
				break;
			}
		puts((yes) ? "YES" : "NO");
	}
	return 0;
}

