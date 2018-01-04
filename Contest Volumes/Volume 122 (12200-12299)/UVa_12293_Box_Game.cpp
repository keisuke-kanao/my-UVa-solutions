
/*
	UVa 12293 - Box Game

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12293_Box_Game.cpp
*/

#include <cstdio>

int main()
{
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		int i = 1;
		do {
			i <<= 1; // i * 2, Alice's turrn
			i++; // Bob's turn
#ifdef DEBUG
			printf("%d\n", i);
#endif
		} while (i < n);
		puts((i == n) ? "Bob" : "Alice");
	}
	return 0;
}

