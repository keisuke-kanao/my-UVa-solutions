
/*
	UVa 468 - Key to Success

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_468_Key_to_Success.cpp
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

const int nr_letters = 26;

struct letter {
	char c_;
	int frequencies_;

	bool operator<(const letter& l) const {return frequencies_ > l.frequencies_;}
};

void init_letter_frequencies(letter* letters)
{
	for (int i = 0; i < nr_letters; i++) {
		letters[i].c_ = 'A' + i;
		letters[i + nr_letters].c_ = 'a' + i;
		letters[i].frequencies_ = letters[i + nr_letters].frequencies_ = 0;
	}
}

void count_letter_frequencies(const char* s, letter* letters)
{
	for ( ; *s; s++) {
		if (isupper(*s))
			letters[*s - 'A'].frequencies_++;
		else
			letters[*s - 'a' + nr_letters].frequencies_++;
	}
}

#ifdef DEBUG
void print_letter_frequencies(letter* letters)
{
	for (int i = 0; letters[i].frequencies_; i++) {
		if (i)
			cout << ' ';
		cout << letters[i].c_ << ':' << letters[i].frequencies_;
	}
	cout << endl;
}
#endif

int main()
{
	int t;
	cin >> t;
	while (t--) {
		string text, encoded_text;
		cin >> text >> encoded_text;
		letter letters[nr_letters * 2], encoded_letters[nr_letters * 2];
		init_letter_frequencies(letters);
		init_letter_frequencies(encoded_letters);
		count_letter_frequencies(text.c_str(), letters);
		count_letter_frequencies(encoded_text.c_str(), encoded_letters);
		sort(letters, letters + nr_letters * 2);
		sort(encoded_letters, encoded_letters + nr_letters * 2);
#ifdef DEBUG
		print_letter_frequencies(letters);
		print_letter_frequencies(encoded_letters);
#endif
		char mappings[nr_letters * 2];
		for (int i = 0; encoded_letters[i].frequencies_; i++) {
			if (isupper(encoded_letters[i].c_))
				mappings[encoded_letters[i].c_ - 'A'] = letters[i].c_;
			else
				mappings[encoded_letters[i].c_ - 'a' + nr_letters] = letters[i].c_;
		}
		for (const char* p = encoded_text.c_str(); *p; p++) {
			if (isupper(*p))
				cout << mappings[*p - 'A'];
			else
				cout << mappings[*p - 'a' + nr_letters];
		}
		cout << endl;
		if (t)
			cout << endl;
	}
	return 0;
}

