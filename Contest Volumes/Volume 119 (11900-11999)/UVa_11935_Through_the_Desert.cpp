
/*
	UVa 11935 - Through the Desert

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11935_Through_the_Desert.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

int main()
{
	double distance_per_litre = 100.0;
	while (true) {
		int p, n;
		const int nr_chars_max = 15;
		char s[nr_chars_max + 1];
		scanf("%d %s %*s %d", &p, s, &n);
		if (!n)
			break;
		int pp = p, l = 0;
		double tank = 0.0, max_tank = 0.0;
		bool goal = false;
		do {
			scanf("%d %s", &p, s);
			int d = p - pp;
			pp = p;
			tank += d / distance_per_litre * n + d * l;
			max_tank = max(max_tank, tank);
			switch (s[0]) {
			case 'F': // "Fuel"
				scanf("%*s %d", &n);
				break;
			case 'L':
				l++;
				break;
			case 'G':
				if (s[1] == 'a') {
					scanf("%*s");
					tank = 0.0;
				}
				else
					goal = true;
				break;
			case 'M':
				l = 0;
				break;
			}
		} while (!goal);
		printf("%.3lf\n", max_tank);
	}
	return 0;
}

