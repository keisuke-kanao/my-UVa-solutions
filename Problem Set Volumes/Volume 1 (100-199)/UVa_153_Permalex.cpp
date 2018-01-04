
/*
	UVa 153 - Permalex

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_153_Permalex.cpp
*/

#include <cstdio>
#include <cstring>

const int nr_letters = 26, nr_chars_max = 30;

int permutation_of_repeated_chars(int length, int letters[])
{
	int nr_denominators = 0, denominators[nr_chars_max];
	for (int i = 0; i < nr_letters; i++)
		for (int j = 2; j <= letters[i]; j++)
			denominators[nr_denominators++] = j;
	long long n = 1, d = 1;
	for (int i = 2; i <= length; i++) {
		n *= i;
		if (nr_denominators > 0)
			d *= denominators[--nr_denominators];
		if (d != 1 && !(n % d)) {
			n /= d;
			d = 1;
		}
	}
	return static_cast<int>(n);
}

int main()
{
	int letters[nr_letters]; // letters[i] is the number of occurrences of ('a' + i)
	while (true) {
		char s[nr_chars_max + 1];
		scanf("%s", s);
		if (s[0] == '#')
			break;
		memset(letters, 0, sizeof(letters));
		int length = strlen(s);
		for (int i = 0; i < length; i++)
			letters[s[i] - 'a']++;
		int sequence = 1;
		for (int i = 0; i < length; i++) {
			int j;
			for (j = 0; j < s[i] - 'a'; j++)
				if (letters[j]) {
					letters[j]--;
					sequence += permutation_of_repeated_chars(length - i - 1, letters);
					letters[j]++;
				}
			letters[j]--;
		}
		printf("%10d\n", sequence);
	}
	return 0;
}

