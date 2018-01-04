
/*
	UVa 12356 - Army Buddies

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12356_Army_Buddies.cpp
*/

#include <cstdio>

const int S_max = 100000;
int lefts[S_max + 1], rights[S_max + 1];
	// lefts[i] is the left of i, rights[i] is the right of i

int main()
{
	while (true) {
		int S, B;
		scanf("%d %d", &S, &B);
		if (!S && !B)
			break;
		for (int i = 1; i <= S; i++) {
			lefts[i] = i - 1;
			rights[i] = i + 1;
		}
		while (B--) {
			int L, R;
			scanf("%d %d", &L, &R);
			if (lefts[L] > 0)
				printf("%d", lefts[L]);
			else
				putchar('*');
			if (rights[R] <= S)
				printf(" %d\n", rights[R]);
			else
				puts(" *");
			lefts[rights[R]] = lefts[L];
			rights[lefts[L]] = rights[R];
		}
		puts("-");
	}
	return 0;
}

