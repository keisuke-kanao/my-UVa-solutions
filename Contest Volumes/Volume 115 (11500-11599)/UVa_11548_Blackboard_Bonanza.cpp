
/*
	UVa 11548 - Blackboard Bonanza

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11548_Blackboard_Bonanza.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int n_max = 70;
int word_lengths[n_max];
char words[n_max][n_max + 1];

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%s", words[i]);
			word_lengths[i] = strlen(words[i]);
		}
		int max_ctr = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (i != j)
					for (int k = 0; k < word_lengths[j]; k++) {
						int m = min(word_lengths[i], word_lengths[j] - k);
						if (m <= max_ctr)
							break;
						int ctr = 0;
						for (int l = 0; l < m; l++)
							if (words[i][l] == words[j][k + l])
								ctr++;
						max_ctr = max(max_ctr, ctr);
					}
		printf("%d\n", max_ctr);
	}
	return 0;
}

