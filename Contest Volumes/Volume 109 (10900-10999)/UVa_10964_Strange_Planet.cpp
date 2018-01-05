
/*
	UVa 10964 - Strange Planet

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10964_Strange_Planet.cpp
*/

#include <cstdio>
#include <cmath>

void get_coordinate(int c, int& x, int& y)
{
	int d = static_cast<int>((1.0 + sqrt(1.0 + static_cast<double>(c) * 2.0)) / 2.0);
		// c is in the d-th diamond shape from the origin
	if (2 * d * (d - 1) == c)
		d--;
	x = 1 - d, y = 1;
	int c_min = 2 * d * (d - 1) + 1, c_max = c_min + d - 1;
	if (c <= c_max)
		x += c - c_min, y += c - c_min;
	else {
		x += c_max - c_min, y += c_max - c_min;
		c_min = c_max, c_max += d;
		if (c <= c_max)
			x += c - c_min, y -= c - c_min;
		else {
			x += c_max - c_min, y -= c_max - c_min;
			c_min = c_max, c_max += d;
			if (c <= c_max)
				x -= c - c_min, y -= c - c_min;
			else {
				x -= c_max - c_min, y -= c_max - c_min;
				c_min = c_max, c_max += d;
				x -= c - c_min, y += c - c_min;
			}
		}
	}
#ifdef DEBUG
	printf("%d: (%d, %d)\n", c, x, y);
#endif
}

int main()
{
	while (true) {
		int a, b;
		scanf("%d %d", &a, &b);
		if (a == -1)
			break;
		int ax, ay, bx, by;
		get_coordinate(a, ax, ay);
		get_coordinate(b, bx, by);
		printf("%.2lf\n", hypot(static_cast<double>(ax - bx), static_cast<double>(ay - by)));
	}
	return 0;
}

