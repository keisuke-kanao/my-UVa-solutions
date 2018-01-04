
/*
	UVa 11412 - Dig the Holes

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11412_Dig_the_Holes.cpp
*/

#include <cstdio>

enum {red, green, blue, yellow, orange, violet};
				//	  A   B     C   D   E   F   G      H   I   J   K   L   M   N   O       P   Q   R    S   T   U   V       W   X   Y       Z
const int color_numbers[] = {-1, blue, -1, -1, -1, -1, green, -1, -1, -1, -1, -1, -1, -1, orange, -1, -1, red, -1, -1, -1, violet, -1, -1, yellow, -1};

const int nr_seqs = 6 * 5 * 4 * 3, nr_colors = violet - red + 1, nr_holes = 4;
int seqs[nr_seqs][nr_holes];

void generate_sequences(int holes, int colors, int seq[], int& si)
{
	if (holes == nr_holes) {
		for (int i = 0; i < nr_holes; i++)
			seqs[si][i] = seq[i];
#ifdef DEBUG
		printf("%d %d %d %d\n", seqs[si][0], seqs[si][1], seqs[si][2], seqs[si][3]);
#endif
		si++;
	}
	else {
		for (int i = 0, b = 1; i < nr_colors; i++, b <<= 1)
			if (!(colors & b)) {
				colors |= b;
				seq[holes] = i;
				generate_sequences(holes + 1, colors, seq, si);
				colors &= ~b;
			}
	}
}

void get_seq(const char* s, int seq[])
{
	for (int i = 0; i < nr_holes; i++)
		seq[i] = color_numbers[s[i] - 'A'];
}

bool possible_sequence(int si, int seq[], int n1, int n2)
{
	int m1 = 0, m2 = 0;
	for (int j = 0; j < nr_holes; j++) {
		int c = seqs[si][j];
		for (int k = 0; k < nr_holes; k++)
			if (seq[k] == c) {
				if (j == k)
					m1++;
				else
					m2++;
				break;
			}
	}
	return n1 == m1 && n2 == m2;
}

int main()
{
	int seq[nr_holes], si = 0;
	generate_sequences(0, 0, seq, si);
#ifdef DEBUG
	printf("%d\n", si);
#endif
	int t;
	scanf("%d", &t);
	while (t--) {
		char s[nr_holes + 1];
		int n11, n12, n21, n22, seq1[nr_holes], seq2[nr_holes];
		scanf("%s %d %d", s, &n11, &n12);
		get_seq(s, seq1);
		scanf("%s %d %d", s, &n21, &n22);
		get_seq(s, seq2);
		bool possible = false;
		for (int si = 0; si < nr_seqs; si++)
			if (possible_sequence(si, seq1, n11, n12) &&
				possible_sequence(si, seq2, n21, n22)) {
				possible = true; break;
			}
		puts((possible) ? "Possible" : "Cheat");
	}
	return 0;
}

