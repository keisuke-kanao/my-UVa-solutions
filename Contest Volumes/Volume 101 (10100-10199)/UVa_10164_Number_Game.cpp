
/*
	UVa 10164 - Number Game

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10164_Number_Game.cpp

	An accepted solution.
*/

#include <cstdio>

const int N_max = 1024;
int N, n, numbers[2 * N_max], solutions[N_max];

bool number_game(int ni, int nr, int s)
{
	if (nr == N)
		return !(s % N);
	else if (ni < n) {
		solutions[nr] = numbers[ni];
		if (number_game(ni + 1, nr + 1, s + numbers[ni]))
			return true;
		if (number_game(ni + 1, nr, s))
			return true;
	}
	return false;
}

int main()
{
	while (true) {
		scanf("%d", &N);
		if (!N)
			break;
		n = 2 * N - 1;
		for (int i = 0; i < n; i++)
			scanf("%d", &numbers[i]);
		if (number_game(0, 0, 0)) {
			puts("Yes");
			for (int i = 0; i < N; i++)
				printf("%d%c", solutions[i], ((i < N - 1) ? ' ' : '\n'));
		}
		else
			puts("No");
	}
	return 0;
}

