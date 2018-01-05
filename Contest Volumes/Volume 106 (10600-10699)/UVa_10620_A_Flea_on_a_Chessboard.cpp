
/*
	UVa 10620 - A Flea on a Chessboard

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10620_A_Flea_on_a_Chessboard.cpp

	from Waterloo local contest 31 January, 2004 Problem C
		(http://acm.student.cs.uwaterloo.ca/~acm00/040131/data/)
*/

#include <cstdio>

int main()
{
	while (true) {
		int S, x, y, dx, dy;
		scanf("%d %d %d %d %d", &S, &x, &y, &dx, &dy);
		if (!S && !x && !y && !dx && !dy)
			break;
		const int jumps_max = 2048;
		int jumps = 0;
		if (!(x % S) && S == dx || !(y % S) && S == dy)
			jumps = -1;
		else {
			for ( ; jumps < jumps_max; x += dx, y += dy, jumps++)
				if (x % S && y % S) {
					int xi = x / S, yi = y / S;
					if (xi & 1 && !(yi & 1) || !(xi & 1) && yi & 1)
						break;
				}
			if (jumps == jumps_max)
				jumps = -1;
		}
		if (jumps != -1)
			printf("After %d jumps the flea lands at (%d, %d).\n", jumps, x, y);
		else
			puts("The flea cannot escape from black squares.");
	}
	return 0;
}


