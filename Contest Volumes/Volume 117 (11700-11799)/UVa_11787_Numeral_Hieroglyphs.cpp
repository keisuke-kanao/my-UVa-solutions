
/*
	UVa 11787 - Numeral Hieroglyphs

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11787_Numeral_Hieroglyphs.cpp
*/

#include <cstdio>
#include <cstring>

int main()
{
	const int symbols[] = {0, 1, 0, 0, 0, 10000, 0, 0, 0, 0, 0, 0, 1000000, 0, 0, 1000, 0, 0, 100, 100000, 10, 0, 0, 0, 0, 0};
	const int units[] = {0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 6, 0, 0, 3, 0, 0, 2, 5, 1, 0, 0, 0, 0, 0};
	const int nr_units = 7;
	int nr_unit_chars[nr_units];

	int n;
	scanf("%d", &n);
	while (n--) {
		const int m_max = 500;
		char hs[m_max + 1];
		scanf("%s", hs);
		memset(nr_unit_chars, 0, sizeof(nr_unit_chars));
		bool error = false;
		int ps = -1, asc = 0;
		for (const char* p = hs; *p; p++) {
			int s = symbols[*p - 'A'];
			if (ps == -1)
				ps = s;
			else if (ps != s) {
				if (asc == 0)
					asc = (ps < s) ? 1 : -1;
				else if (asc == 1 && ps > s || asc == -1 && ps < s) {
					error = true; break;
				}
				ps = s;
			}
			if (++nr_unit_chars[units[*p - 'A']] > 9) {
				error = true; break;
			}
		}
		if (error)
			puts("error");
		else {
			int nr = 0;
			for (int i = nr_units - 1; i >= 0; i--) {
				nr *= 10;
				nr += nr_unit_chars[i];
			}
			printf("%d\n", nr);
		}
	}
	return 0;
}

