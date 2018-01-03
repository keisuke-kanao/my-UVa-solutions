
/*
	UVa 642 - Word Amalgamation

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_642_Word_Amalgamation.cpp
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int nr_words_max = 100;
string dictionary[nr_words_max + 1];
const string terminator("XXXXXX");

int main()
{
	int nr_words = 0;
	while (true) {
		cin >> dictionary[nr_words];
		if (dictionary[nr_words] == terminator)
			break;
		nr_words++;
	}
	sort(dictionary, dictionary + nr_words);
	while (true) {
		string word;
		cin >> word;
		if (word == terminator)
			break;
		bool found = false;
		sort(word.begin(), word.end());
		do {
			if (binary_search(dictionary, dictionary + nr_words, word)) {
				found = true;
				cout << word << endl;
			}
		} while (next_permutation(word.begin(), word.end()));
		if (!found)
			cout << "NOT A VALID WORD\n";
		cout << "******\n";
	}
	return 0;
}

