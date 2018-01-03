
/*
	UVa 1368 - DNA Consensus String

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1368_DNA_Consensus_String.cpp
*/

#include <cstdio>

const int nr_chars = 4, m_max = 50, n_max = 1000;
char seqs[m_max][n_max + 1], consensus[n_max + 1];

const char nucleotides[] = {'A', 'C', 'G', 'T'};
const int indices[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int m, n;
		scanf("%d %d", &m, &n);
		for (int i = 0; i < m; i++)
			scanf("%s", seqs[i]);
		int error = 0;
		for (int i = 0; i < n; i++) {
			int freqs[nr_chars] = {0, 0, 0, 0};
			for (int j = 0; j < m; j++)
				freqs[indices[seqs[j][i]]]++;
			int max_f = freqs[0], max_j = 0;
			for (int j = 1; j < nr_chars; j++)
				if (freqs[j] > max_f) {
					max_f = freqs[j], max_j = j;
				}
			consensus[i] = nucleotides[max_j];
			error += m - max_f;
		}
		consensus[n] = '\0';
		printf("%s\n%d\n", consensus, error);
	}
	return 0;
}

