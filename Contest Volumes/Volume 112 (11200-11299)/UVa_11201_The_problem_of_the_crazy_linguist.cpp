
/*
	UVa 11201 - The problem of the crazy linguist

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11201_The_problem_of_the_crazy_linguist.cpp
*/

#include <cstdio>
#include <cstring>


const int nr_chars_max = 7, nr_letters = 26, nr_odd_letters = 21, nr_even_letters = 5;
const char odd_letters[nr_odd_letters] = {
	'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};
const char even_letters[nr_even_letters] = {'a', 'e', 'i', 'o', 'u'};

const double probabilities[nr_letters] = {
	12.53, 1.42, 4.68, 5.86, 13.68, 0.69, 1.01, 0.70, 6.25, 0.44, 0.00, 4.97, 3.15,
	6.71, 8.68, 2.51, 0.88, 6.87, 7.98, 4.63, 3.93, 0.90, 0.02, 0.22, 0.90, 0.52
};

double SBC(const char* s)
{
	double sbc = 0.0;
	for (int i = 1; *s; i++, s++)
		sbc += probabilities[*s - 'a'] * i;
	return sbc;
}

void SBC_patterns(int n, int si, char s[], int freqs[], int& nr_patterns, double& sum)
{
	if (si == n) {
		nr_patterns++;
		sum += SBC(s);
/*
#ifdef DEBUG
		printf("%d %s %.2lf\n", nr_patterns, s, sum);
#endif
*/
	}
	else if (!(si & 1)) {
		for (int i = 0; i < nr_odd_letters; i++) {
			int j = odd_letters[i] - 'a';
			if (freqs[j] < 2) {
				freqs[j]++;
				s[si] = odd_letters[i];
				SBC_patterns(n, si + 1, s, freqs, nr_patterns, sum);
				freqs[j]--;
			}
		}
	}
	else {
		for (int i = 0; i < nr_even_letters; i++) {
			int j = even_letters[i] - 'a';
			if (freqs[j] < 2) {
				freqs[j]++;
				s[si] = even_letters[i];
				SBC_patterns(n, si + 1, s, freqs, nr_patterns, sum);
				freqs[j]--;
			}
		}
	}
}

int main()
{
	int N;
	scanf("%d", &N);
	while (N--) {
		char s[nr_chars_max + 1];
		scanf("%s", s);
		double sbc = SBC(s), sum = 0.0;
		int n = strlen(s), nr_patterns = 0, freqs[nr_letters];
		memset(freqs, 0, sizeof(freqs));
		freqs[s[0] - 'a']++;
		SBC_patterns(n, 1, s, freqs, nr_patterns, sum);
#ifdef DEBUG
		printf("%.2lf %d %.2lf\n", sbc, nr_patterns, sum);
#endif
		double average = sum / nr_patterns;
		puts((sbc >= average) ? "above or equal" : "below");
	}
	return 0;
}

