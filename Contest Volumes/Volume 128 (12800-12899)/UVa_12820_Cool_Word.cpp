
/*
	UVa 12820 - Cool Word

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12820_Cool_Word.cpp
*/

#include <algorithm>
#include <functional>
#include <cstdio>
using namespace std;

int main()
{
	const int nr_letters = 'z' - 'a' + 1, nr_chars_max = 30;
	for (int c = 1; ; c++) {
		int n;
		if (scanf("%d", &n) == EOF)
			break;
		int nr_cool_words = 0;
		while (n--) {
			char word[nr_chars_max + 1];
			scanf("%s", word);
			int freqs[nr_letters] = {};
			int length = 0;
			for (char* p = word; *p; p++, length++)
				freqs[*p - 'a']++;
			bool cool = false;
			if (length > 1) {
				sort(freqs, freqs + nr_letters, greater<int>());
				if (freqs[0] < length) {
					cool = true;
					for (int i = 1; i < nr_letters && freqs[i]; i++)
						if (freqs[i - 1] == freqs[i]) {
							cool = false;
							break;
						}
				}
			}
			if (cool)
				nr_cool_words++;
		}
		printf("Case %d: %d\n", c, nr_cool_words);
	}
	return 0;
}

