
/*
	UVa 10506 - The Ouroboros problem

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10506_The_Ouroboros_problem.cpp
*/

#include <cstdio>
#include <cmath>
using namespace std;

const int nr_sequences_max = 65536;
char sequences[nr_sequences_max];
bool visited[nr_sequences_max];
int M, N, nr_sequences;

bool ouroboros(int si, int integer)
{
	if (si == nr_sequences - 1)
		return true;
	int i = (integer * N) % nr_sequences;
	for (int j = 0; j < N; j++)
		if (!visited[i + j]) {
			visited[i + j] = true;
#ifdef DEBUG
		putchar('\n');
		for (int k = 0; k < si; k++)
			putchar(' ');
		putchar('0' + j);
#endif
		if (ouroboros(si + 1, i + j)) {
			sequences[si] = '0' + j;
			return true;
		}
		visited[i + j] = false;
	}
	return false; // actually, never reached here
}

int main()
{
	while (scanf("%d %d", &M, &N) != EOF) {
		nr_sequences = static_cast<int>(pow(static_cast<double>(N), static_cast<double>(M)));
		if (N > 1) {
			for (int i = 0; i < nr_sequences; i++)
				visited[i] = false;
			visited[0] = true;
			ouroboros(0, 0);
			for (int i = 0; i < M; i++)
				putchar('0');
			for (int i = 0; i < nr_sequences - M; i++)
				putchar(sequences[i]);
		}
		else
			putchar('0');
		putchar('\n');
	}
	return 0;
}

