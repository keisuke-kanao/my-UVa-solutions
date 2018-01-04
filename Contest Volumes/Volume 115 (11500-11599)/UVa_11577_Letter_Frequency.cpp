
/*
	UVa 11577 - Letter Frequency

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11577_Letter_Frequency.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cctype>
using namespace std;

struct letter_frequency {
	char letter_;
	int frequency_;
	bool operator<(const letter_frequency& lf) const {return frequency_ > lf.frequency_;}
};

int main()
{
	const int nr_letters = 26, nr_chars_max = 200;
	letter_frequency letter_frequencies[nr_letters];
	int t;
	scanf("%d\n", &t);
	while (t--) {
		char s[nr_chars_max + 1];
		gets(s);
		for (int i = 0; i < nr_letters; i++) {
			letter_frequencies[i].letter_ = 'a' + i;
			letter_frequencies[i].frequency_ = 0;
		}
		for (const char* p = s; *p; p++)
			if (isalpha(*p))
				letter_frequencies[tolower(*p) - 'a'].frequency_++;
		stable_sort(letter_frequencies, letter_frequencies + nr_letters);
		int f = letter_frequencies[0].frequency_;
		putchar(letter_frequencies[0].letter_);
		for (int i = 1; i < nr_letters && letter_frequencies[i].frequency_ == f; i++)
			putchar(letter_frequencies[i].letter_);
		putchar('\n');
	}
	return 0;
}

