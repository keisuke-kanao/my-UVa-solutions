
/*
	UVa 10391 - Compound Words

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10391_Compound_Words.cpp

	from 19 June, 2011 - Waterloo local contest Question D
		http://plg1.cs.uwaterloo.ca/~acm00/110619/)
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int nr_words_max = 120000;
char* pwords[nr_words_max]; // pwords[i] is the i-th word string

int compare_word(const void* s, const void* t)
{
	return strcmp(*(const char**)s, *(const char**)t);
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	int nr_words = 0;
	size_t max_word_length = 0;
	string s;
	while (cin >> s) {
		size_t length = s.length();
		max_word_length = max(max_word_length, length);
		pwords[nr_words] = new char[length + 1];
		strcpy(pwords[nr_words], s.c_str());
		nr_words++;
	}
	char* pw = new char[max_word_length + 2];
	for (int i = 0; i < nr_words; i++) {
		strcpy(pw + 1, pwords[i]);
		for (char *qw = pw, *rw = pw + 2; *rw; qw++, rw++) {
			*qw = *(qw + 1); *(qw + 1) = '\0'; // divide the word by inserting a '\0'
			if (bsearch(&pw, pwords, nr_words, sizeof(char*), compare_word) &&
				bsearch(&rw, pwords, nr_words, sizeof(char*), compare_word)) {
				cout << pwords[i] << endl;
				break;
			}
		}
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

