
/*
	2.8.4 Crypt Kicker
	PC/UVa IDs: 110204/843, Popularity: B, Success rate: low Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_843_Crypt_Kicker.cpp
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

const int nr_letters = 'z' - 'a' + 1;

struct word {
	string encrypted;
	string decrypted;

	word(string s) : encrypted(s) {}
};

bool compare_length(const word& i, const word& j)
{
	return i.encrypted.length() > j.encrypted.length();
}

bool injective(const vector<char>& decrypted_letters)
{
	vector<unsigned char> f(nr_letters, 0);
	for (int i = 0; i < nr_letters; i++)
		if (decrypted_letters[i] != '*') {
			int di = decrypted_letters[i] - 'a';
			if (f[di])
				return false;
			else
				f[di] = 1;
		}
	return true;
}

bool match(const string& encrypted, const string& decrypted, vector<char>& decrypted_letters)
{
	for (int i = 0; i < encrypted.size(); i++) {
		char dc = decrypted_letters[encrypted[i] - 'a'];
		if (dc != '*' && dc != decrypted[i])
			return false;
		else
			decrypted_letters[encrypted[i] - 'a'] = decrypted[i];
	}
	return injective(decrypted_letters);
}

bool backtrack(int word_i, vector<word>& words, vector<char>& decrypted_letters,
	const vector<string>& dictionary, const vector< vector<int> >& dictionary_indices)
{
	if (word_i == words.size()) // all of the words have been decrypted
		return true;
	word& w = words[word_i];
	vector<int> indices = dictionary_indices[word_i];
	for (int i = 0; i < indices.size(); i++) {
		vector<char> dl(decrypted_letters);
		string dw = dictionary[indices[i]];
		if (match(w.encrypted, dw, dl)) {
			w.decrypted = dw;
			if (backtrack(word_i + 1, words, dl, dictionary, dictionary_indices)) {
				decrypted_letters = dl;
				return true;
			}
		}
	}
	return false;
}

int main(int /* argc */, char** /* argv */)
{
	string line;
	int nr_dictionary_words;
	cin >> nr_dictionary_words;
	getline(cin, line); // read and discard the newline character
	vector<string> dictionary; // dictionary of words
	while (nr_dictionary_words--) {
		getline(cin, line);
		dictionary.push_back(line);
	}
	istringstream iss;
	while (getline(cin, line)) {
		iss.str(line);
		string s;
		vector<word> words;
		while (iss >> s)
			words.push_back(word(s));
		iss.clear();
		sort(words.begin(), words.end(), compare_length); // sort the words in descending order of length
		vector< vector<int> > dictionary_indices(words.size());
		for (int i = 0; i < words.size(); i++) {
			int length = words[i].encrypted.length();
			vector<int>& indices = dictionary_indices[i]; // vector of indices to the dictionary words of same length
			for (int j = 0; j < dictionary.size(); j++)
				if (dictionary[j].length() == length)
					indices.push_back(j);
		}
		vector<char> decrypted_letters(nr_letters, '*');
		backtrack(0, words, decrypted_letters, dictionary, dictionary_indices);
		iss.str(line);
		bool words_printed = false;
		while (iss >> s) {
			if (words_printed)
				cout << ' ';
			words_printed = true;
			for (int i = 0; i <s.length(); i++)
				cout << decrypted_letters[s[i] - 'a'];
		}
		cout << endl;
		iss.clear();
	}
	return 0;
}

