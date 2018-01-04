
/*
	UVa 12150 - Pole Position

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12150_Pole_Position.cpp
*/

#include <cstdio>

const int N_max = 1000;
int cars[N_max + 1];

int main()
{
	while (true) {
		int N;
		scanf("%d", &N);
		if (!N)
			break;
		for (int i = 1; i <= N; i++)
			cars[i] = 0;
		bool valid = true;
		for (int i = 1; i <= N; i++) {
			int C, P;
			scanf("%d %d", &C, &P);
			if (valid) {
				int sp = i + P;
				if (sp >= 1 && sp <= N) {
					if (cars[sp])
						valid = false;
					else
						cars[sp] = C;
				}
				else
					valid = false;
			}
		}
		if (valid)
			for (int i = 1; i <= N; i++)
				printf("%d%c", cars[i], ((i < N) ? ' ' : '\n'));
		else
			puts("-1");
	}
	return 0;
}

/*
Sample input

4
1 0
3 1
2 -1
4 0
4
22 1
9 1
13 0
21 -2
3
19 1
9 -345
17 0
7
2 2
8 0
5 -2
7 1
1 1
9 1
3 -3
0

Output for the sample input

1 2 3 4
-1
-1
5 8 2 3 7 1 9

*/

