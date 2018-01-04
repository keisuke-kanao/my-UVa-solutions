
/*
	UVa 11834 - Elevator

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11834_Elevator.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

inline int square(int i)
{
	return i * i;
}

int main()
{
	const double d = 1.0 + 1.0 / sqrt(2.0);
	while (true) {
		int L, C, R1, R2;
		scanf("%d %d %d %d", &L, &C, &R1, &R2);
		if (!L)
			break;
		if (L < C)
			swap(L, C);
		if (R1 < R2)
			swap(R1, R2);
		int R = R1 + R2;
		puts((C < R1 * 2 || square(R) > square(L - R) + square(C - R)) ? "N" : "S");
	}
	return 0;
}

