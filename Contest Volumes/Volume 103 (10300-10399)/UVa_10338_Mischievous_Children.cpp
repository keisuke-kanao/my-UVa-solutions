
/*
	UVa 10338 - Mischievous Children

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10338_Mischievous_Children.cpp
*/

#include <cstdio>
#include <cstring>

int main()
{
	const int nr_chars_max = 20;
	long long factorials[nr_chars_max + 1];
	factorials[0] = 1;
	for (int i = 1; i <= nr_chars_max; i++)
		factorials[i] = factorials[i - 1] * i;
#ifdef DEBUG
	printf("%lld\n", factorials[nr_chars_max]);
#endif
	const int nr_letters = 26;
	int frequencies[nr_letters]; // frequencies[i] is the number of occurrences of (i + 'A')
	int ds;
	scanf("%d", &ds);
	for (int s = 1; s <= ds; s++) {
		memset(frequencies, 0, sizeof(frequencies));
		char word[nr_chars_max + 1];
		scanf("%s", word);
		int length = strlen(word);
		for (int i = 0; i < length; i++)
			frequencies[word[i] - 'A']++;
		long long f = factorials[length];
		for (int i = 0; i < nr_letters; i++)
			if (frequencies[i])
				f /= factorials[frequencies[i]];
		printf("Data set %d: %lld\n", s, f);
	}
	return 0;
}

