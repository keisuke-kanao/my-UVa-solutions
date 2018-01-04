
/*
	UVa 12366 - King's Poker

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12366_Kings_Poker.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

int main()
{
	while (true) {
		int A, B, C;
		scanf("%d %d %d", &A, &B, &C);
		if (!A)
			break;
		// sort A, B, and C in ascending order
		if (A > B)
			swap(A, B);
		if (B > C)
			swap(B, C);
		if (A > B)
			swap(A, B);
		if (A == B && B == C) { // set
			if (A == 13)
				A = 0; // impossible
			else
				A = B = C = ++A;
		}
		else if (A == B) { // pair
			if (C == 13)
				A = 1, B = C = ++B;
			else
				C++;
		}
		else if (B == C) { // pair
			if (A == 12 && B == 13)
				A = B = C = 1;
			else if (A + 1 == B)
				A = C, C = B + 1;
			else
				A++;
		}
		else { // no-pair
			A = B = 1, C = 2;
		}
		if (A)
			printf("%d %d %d\n", A, B, C);
		else
			puts("*");
	}
	return 0;
}

