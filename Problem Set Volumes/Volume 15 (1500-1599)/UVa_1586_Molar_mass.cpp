
/*
	UVa 1586 - Molar mass

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1586_Molar_mass.cpp
*/

#include <cstdio>
#include <cstdlib>

int main()
{
	const int nr_chars_max = 80;
	const double w_carbon = 12.01, 	w_hydrogen = 1.008, w_oxygen = 16.00, w_nitrogen = 14.01;
	int T;
	scanf("%d", &T);
	while (T--) {
		char s[nr_chars_max + 1];
		scanf("%s", s);
		int carbon = 0, hydrogen = 0, oxygen = 0, nitrogen = 0;
		for (char* p = s; *p; ) {
			char* pe = p + 1;
			if (*p == 'C' || *p == 'H' || *p == 'O' || *p == 'N') {
				int n = strtol(p + 1, &pe, 10);
				if (!n)
					n = 1;
				switch (*p) {
				case 'C':
					carbon += n; break;
				case 'H':
					hydrogen += n; break;
				case 'O':
					oxygen += n; break;
				case 'N':
					nitrogen += n; break;
				}
			}
			p = pe;
		}
		double w = w_carbon * carbon + w_hydrogen * hydrogen + w_oxygen * oxygen + w_nitrogen * nitrogen;
		printf("%.3lf\n", w);
	}
	return 0;
}

