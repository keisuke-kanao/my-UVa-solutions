
/*
	UVa 10785 - The Mad Numerologist

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10785_The_Mad_Numerologist.cpp
*/

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int main()
{
	const int n_max = 210, vowels_usage_max = 21, consonants_usage_max = 5;
	const char vowel_letters[] = {'A', 'U', 'E', 'O', 'I'};
	const char consonant_letters[] = {'J', 'S', 'B', 'K', 'T', 'C', 'L', 'D', 'M', 'V', 'N', 'W',
		'F', 'X', 'G', 'P', 'Y', 'H', 'Q', 'Z', 'R'};
	int nr_cases;
	cin >> nr_cases;
	for (int c = 1; c <= nr_cases; c++) {
		int n;
		cin >> n;
		int nr_vowels = (n + 1) / 2, nr_consonants = n / 2;
		char vowels[n_max + 1], consonants[n_max + 1];

		for (int i = 0, j = 0; i < nr_vowels; j++) {
			int k = min(nr_vowels - i, vowels_usage_max);
			memset(vowels + i, vowel_letters[j], k);
			i += k;
		}
		for (int i = 0, j = 0; i < nr_consonants; j++) {
			int k = min(nr_consonants - i, consonants_usage_max);
			memset(consonants + i, consonant_letters[j], k);
			i += k;
		}
		sort(vowels, vowels + nr_vowels);
		sort(consonants, consonants + nr_consonants);
		char name[n_max + 1];
		for (int i = 0; i < nr_vowels; i++)
			name[2 * i] = vowels[i];
		for (int i = 0; i < nr_consonants; i++)
			name[2 * i + 1] = consonants[i];
		name[nr_vowels + nr_consonants] = '\0';
		cout << "Case " << c << ": " << name << endl;
	}
	return 0;
}

