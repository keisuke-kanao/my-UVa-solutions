
/*
	UVa 12577 - Hajj-e-Akbar

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_12577_Hajj-e-Akbar.cpp
*/

#include <cstdio>

int main()
{
	const int nr_chars_max = 16;
	char s[nr_chars_max];
	for (int case_nr = 1; ; case_nr++) {
		gets(s);
		if (s[0] == '*')
			break;
		printf("Case %d: %s\n", case_nr, ((s[0] == 'H') ? "Hajj-e-Akbar" : "Hajj-e-Asghar"));
	}
	return 0;
}

