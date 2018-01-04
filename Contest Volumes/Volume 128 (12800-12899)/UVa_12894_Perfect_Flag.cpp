
/*
	UVa 12894 - Perfect Flag

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12894_Perfect_Flag.cpp
*/

#include <cstdio>

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int x0, y0, x1, y1, cx, cy, r;
		scanf("%d %d %d %d %d %d %d", &x0, &y0, &x1, &y1, &cx, &cy, &r);
		int l = x1 - x0, w = y1 - y0;
		bool valid = l && w && l * 6 == w * 10 && l == r * 5 &&
			l * 9 == (cx - x0) * 20 && w == (cy - y0) * 2;
		puts((valid) ? "YES" : "NO");
	}
	return 0;
}

