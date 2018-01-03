
/*
	UVa 587 - There's treasure everywhere!

	To build using Visual Studio 2008:
		cl -EHsc UVa_587_Theres_treasure_everywhere.cpp

	from ACM Western and Southwestern European Regionals 1997
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_EU_SWERC/1997/index.html)
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

int main()
{
	const double sqrt2 = sqrt(2.0);
	const struct direction {
		const char* d_;
		double x_, y_;
	} directions[] = {
		{"N", 0.0, 1.0}, {"NE", 1.0 / sqrt2, 1.0 / sqrt2}, {"E", 1.0, 0.0}, {"SE", 1.0 / sqrt2, -1.0 / sqrt2},
		{"S", 0.0, -1.0}, {"SW", -1.0 / sqrt2, -1.0 / sqrt2}, {"W", -1.0, 0.0}, {"NW", -1.0 / sqrt2, 1.0 / sqrt2}
	};

	for (int m = 1; ; m++) {
		const int nr_chars_max = 200;
		char s[nr_chars_max + 1];
		gets(s);
		if (!strcmp(s, "END"))
			break;
		double x = 0.0, y = 0.0;
		char* p = s;
		while (*p) {
			char* q;
			int l = static_cast<int>(strtol(p, &q, 0));
			p = q;
			if (*++p != ',' && *p != '.')
				p++;
			// at this point, p points either ',' or '.'
			*p++ = '\0';
			for (size_t i = 0, e = sizeof(directions) / sizeof(directions[0]); i < e; i++)
				if (!strcmp(q, directions[i].d_)) {
					x += directions[i].x_ * l;
					y += directions[i].y_ * l;
					break;
				}
		}
		printf("Map #%d\n", m);
		printf("The treasure is located at (%.3lf,%.3lf).\n", x, y);
		printf("The distance to the treasure is %.3lf.\n\n", sqrt(x * x + y * y));
	}
	return 0;
}

