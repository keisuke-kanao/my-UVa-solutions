
/*
	UVa 129 - Krypton Factor

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_129_Krypton_Factor.cpp
*/

#include <cstdio>

const int nr_chars_max = 80;
char sequence[nr_chars_max + 1];

bool is_hard_sequence(int length)
{
	for (int k = 1; k <= length / 2; k++) {
		int i, j;
		for (i = length - 1, j = 0; j < k; i--, j++)
			if (sequence[i] != sequence[i - k])
				break;
		if (j == k)
			return false;
	}
	return true;
}

int hard_sequences(int L, int& n, int si)
{
	for (int i = 0; i < L; i++) {
		sequence[si] = 'A' + i;
		if (is_hard_sequence(si + 1)) {
			n--;
#ifdef DEBUG
			sequence[si + 1] = '\0';
			printf("%d: %s\n", n, sequence);
#endif
			if (!n)
				return si + 1;
			int result = hard_sequences(L, n, si + 1);
			if (result > 0)
				return result;
		}
	}
	return -1;
}

int main()
{
	while (true) {
		int n, L;
		scanf("%d %d", &n, &L);
		if (!n)
			break;
		int length = hard_sequences(L, n, 0);
		for (int i = 0, j = 0; i < length; i++) {
			putchar(sequence[i]);
			if (i == length - 1)
				putchar('\n');
			else if (i % 4 == 3) {
				if (++j == 16)
					putchar('\n');
				else
					putchar(' ');
			}
		}
		printf("%d\n", length);
	}
	return 0;
}

