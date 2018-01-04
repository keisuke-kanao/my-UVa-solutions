
/*
	UVa 11505 - Logo

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11505_Logo.cpp
*/

#include <cstdio>
#include <cmath>

int main()
{
	const double pi = 2.0 * acos(0.0);
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		double x = 0.0, y = 0.0, a = 0.0;
		while (n--) {
			char s[3];
			double d;
			scanf("%s %lf", s, &d);
			switch (s[0]) {
			case 'f': // fd
				x += d * cos(a); y += d * sin(a);
				break;
			case 'b': // bk
				x -= d * cos(a); y -= d * sin(a);
				break;
			case 'l': // lt
				a += (d * pi) / 180.0; break;
			case 'r': // rt
				a -= (d * pi) / 180.0; break;
			}
		}
		printf("%.0lf\n", sqrt(x * x + y * y));
	}
	return 0;
}

