
/*
	UVa 12643 - Tennis Rounds

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12643_Tennis_Rounds.cpp
*/

#include <cstdio>

int main()
{
	int N, i, j;
	while (scanf("%d %d %d", &N, &i, &j) != EOF) {
		int r = 0;
		do {
			i = (i + 1) / 2, j = (j + 1) / 2;
			r++;
		} while (i != j);
		printf("%d\n", r);
	}
	return 0;
}

/*

Sample Input

3 2 5
3 5 7
2 1 2
2 2 1

Sample Output

3
2
1
1

*/

