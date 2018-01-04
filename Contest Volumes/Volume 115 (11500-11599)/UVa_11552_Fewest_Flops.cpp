
/*
	UVa 11552 - Fewest Flops

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11552_Fewest_Flops.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_letters = 26, nr_chars_max = 1000, infinite = nr_chars_max + 1;
int nr_chunks[nr_chars_max]; // number of chunks in Si
int freqs[nr_chars_max][nr_letters];
	// freqs[i][j] is the number of occurrences of ('a' + j) charactor in Si
int min_nr_chunks[nr_chars_max][nr_letters];
	// min_nr_chunks[i][j] min. number of chunks up to Si with the last character of of j

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		int k;
		char S[nr_chars_max + 1];
		scanf("%d %s", &k, S);
		int length = strlen(S), n = length / k;
		for (int i = 0, si = 0; i < n; i++, si += k) {
			nr_chunks[i] = 0;
			memset(&freqs[i], 0, sizeof(freqs[0]));
			for (int j = 0; j < k; j++)
				if (!freqs[i][S[si + j] - 'a']++)
					nr_chunks[i]++;
		}
		for (int j = 0; j < nr_letters; j++)
			min_nr_chunks[0][j] = (freqs[0][j]) ? nr_chunks[0] : infinite;
		for (int i = 1; i < n; i++)
			for (int j = 0; j < nr_letters; j++)
				min_nr_chunks[i][j] = infinite;

#ifdef DEBUG
		for (int j = 0; j < nr_letters; j++)
			if (min_nr_chunks[0][j] < infinite)
				printf("[0][%c]: %d ", 'a' + j, min_nr_chunks[0][j]);
		putchar('\n');
#endif
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < nr_letters; j++) {
				if (freqs[i][j])
					for (int k = 0; k < nr_letters; k++)
						if (freqs[i + 1][k]) {
							int nr = 0;
							if (j != k)
								nr = (freqs[i + 1][j]) ? nr_chunks[i + 1] - 1 : nr_chunks[i + 1];
							else if (nr_chunks[i + 1] != 1) // j == k
								nr = nr_chunks[i + 1];
							min_nr_chunks[i + 1][k] = min(min_nr_chunks[i + 1][k], min_nr_chunks[i][j] + nr);
						}
			}
#ifdef DEBUG
			for (int j = 0; j < nr_letters; j++)
				if (min_nr_chunks[i + 1][j] < infinite)
					printf("[%d][%c]: %d ", i + 1, 'a' + j, min_nr_chunks[i + 1][j]);
			putchar('\n');
#endif
		}
		int min_nr = infinite;
		for (int j = 0; j < nr_letters; j++)
			min_nr = min(min_nr, min_nr_chunks[n - 1][j]);
		printf("%d\n", min_nr);
	}
	return 0;
}

