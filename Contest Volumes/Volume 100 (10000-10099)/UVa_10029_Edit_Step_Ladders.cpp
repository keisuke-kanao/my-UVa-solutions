
/*
	9.6.5 Edit Step Ladders
	PC/UVa IDs: 110905/10029, Popularity: B, Success rate: low Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10029_Edit_Step_Ladders.cpp
*/

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstring>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

#define LETTERS_MAX	16 // max. number of letters of a word
#define	WORDS_MAX	25000 // max. number of words

char words[WORDS_MAX][LETTERS_MAX + 3]; // 475,000 bytes
int esl_lengths[WORDS_MAX]; // esl_lengths[i] is the edit step ladder length of words[i]

int insert_esl_words(int i, const string& s, int esl_length, map<string, int>& esl_words)
{
	map<string, int>::iterator j = esl_words.find(s);
	if (j != esl_words.end()) {
		esl_length = max(esl_length, esl_lengths[j->second]);
		j->second = i;
	}
	else
		esl_words.insert(make_pair(s, i));
	return esl_length;
}

int main(int /* argc */, char** /* argv */)
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	int n = 0;
	while (scanf("%s", &words[n][1]) == 1)
		words[n++][0] = ' '; // the original word is preceded by a space character
	map<string, int> esl_words;
		// key is a modified word that comprises an edit step and value is the index to the original word
	int max_esl_length = 0;
	for (int i = n - 1; i >= 0; i--) {
		int esl_length = -1;
		char* w = &words[i][1];
		for (char* p = w; *p; p++) {
			// generate and register a word in which a character in the original word is replaced with a space character
			char c = *p; *p = ' ';
			esl_length = insert_esl_words(i, w, esl_length, esl_words);
			*p = c;
		}
		w = words[i];
		for (char* p = w; ; p++) {
			// generate and register a word in which a space is inserted between the characters of the original word
			esl_length = insert_esl_words(i, w, esl_length, esl_words);
			if (!*(p + 1))
				break;
			*p = *(p + 1); *(p + 1) = ' ';
		}
/*
		Since for each word of length m, at most (2 * m + 1) words are registered to esl_words, 
		the number of entries in esl_words are at most WORDS_MAX * (2 * LETTERS_MAX + 1) = 825,000.
*/
		esl_lengths[i] = esl_length + 1;
#ifdef DEBUG
		cerr << w << ' ' << esl_lengths[i] << endl;
#endif
		max_esl_length = max(max_esl_length, esl_lengths[i]);
	}
	cout << max_esl_length + 1 << endl;
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

