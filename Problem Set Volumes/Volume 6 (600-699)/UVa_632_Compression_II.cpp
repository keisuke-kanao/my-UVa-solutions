
/*
	UVa 632 - Compression (II)

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_632_Compression_II.cpp
*/

#include <cstdio>
#include <cstring>

const int N_max = 1997, nr_line_chars_max = 50, nr_chars = 128;
char S[N_max + 1], t[N_max + 1];
int cindices[N_max + 1], nindices[N_max + 1];

int main()
{
	int M;
	scanf("%d", &M);
	while (M--) {
		int N;
		scanf("%d", &N);
		while (getchar() != '\n')
			;
		for (char* p = S; p - S < N; p += strlen(p))
			gets(p);
		for (int i = 0; i < N; i++)
			cindices[i] = i;
#ifdef DEBUG
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				putchar(S[(cindices[i] + j) % N]);
			putchar('\n');
		}
#endif
		for (int i = N - 1; i >= 0; i--) { // LSD radix sort
			int counts[nr_chars] = {};
			for (int j = 0; j < N; j++)
				counts[S[(cindices[j] + i) % N] + 1]++;
			for (int j = 1; j < nr_chars; j++)
				counts[j] += counts[j - 1];
			for (int j = 0; j < N; j++)
				nindices[counts[S[(cindices[j] + i) % N]]++] = cindices[j];
			for (int j = 0; j < N; j++)
				cindices[j] = nindices[j];
		}
		int r = 0;
		for (int i = 0; i < N; i++) {
#ifdef DEBUG
			for (int j = 0; j < N; j++)
				putchar(S[(cindices[i] + j) % N]);
			putchar('\n');
#endif
			if (cindices[i] == 1)
				r = i;
			t[i] = S[(cindices[i] + N - 1) % N];
		}
		t[N] = '\0';
		printf("%d\n", r);
		for (char* p = t; ; ) {
			if (N > nr_line_chars_max) {
				char c = p[nr_line_chars_max];
				p[nr_line_chars_max] = '\0';
				puts(p);
				p[nr_line_chars_max] = c;
				p += nr_line_chars_max, N -= nr_line_chars_max;
			}
			else {
				puts(p);
				break;
			}
		}
		if (M)
			putchar('\n');
	}
	return 0;
}

