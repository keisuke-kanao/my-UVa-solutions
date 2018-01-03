
/*
	UVa 545 - Heads

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_545_Heads.cpp
*/

#include <cstdio>
#include <cmath>

const int n_max = 9000;

struct probability {
	double x_;
	int y_;
} probabilities[n_max + 1];

int main()
{
	const double eps = 1.0e-9; // without this value, the vridict was WA.
	int n, y = 0;
	double x = 1.0;
	probabilities[0].x_ = x; probabilities[0].y_ = y;
	for (n = 1; n <= n_max; n++) {
		x /= 2.0;
		if (x < 1.0) {
			x *= 10.0;
			y++;
		}
		probabilities[n].x_ = x; probabilities[n].y_ = y;
	}
	int r;
	scanf("%d", &r);
	while (r--) {
		int n;
		scanf("%d", &n);
		printf("2^-%d = %.3lfE-%d\n", n, probabilities[n].x_ + eps, probabilities[n].y_);
	}
	return 0;
}

