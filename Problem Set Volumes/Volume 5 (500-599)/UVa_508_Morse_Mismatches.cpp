
/*
	UVa 508 - Morse Mismatches

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_508_Morse_Mismatches.cpp

	An accepted solution.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <limits>
using namespace std;

const size_t infinite = numeric_limits<size_t>::max();
map<char, string> morse_codes; // keys are 'A' - 'Z' or '0'- '9', values are morse code
map<string, string> context_words; // keys are context words, values are their morse codes

size_t diff(string a, string b)
{
	if(a == b)
		return 0;
	if (a.size() > b.size())
		swap(a, b);
    if (a == b.substr(0, a.length()))
		return b.length() - a.length();
	else
		return infinite;
}
void print_word(const string& code)
{
	size_t min_diff = infinite;
	string word;
	for (map<string, string>::const_iterator i = context_words.begin(); i != context_words.end(); ++i) {
		size_t d = diff(code, i->second);
		if(d < min_diff) {
			min_diff = d, word = i->first;
		}
		else if (d == 0 && min_diff == 0) {
			cout << word << "!\n";
			return;
		}
	}
	if (min_diff)
		cout << word << "?\n";
	else
		cout << word << endl;
}

int main()
{
	while (true) {
		string c, code;
		cin >> c;
		if (c == "*")
			break;
 		cin >> code;
		morse_codes[c[0]] = code;
    }
	while (true) {
		string word;
		cin >> word;
		if (word == "*")
			break;
		string code;
		for (const char* p = word.c_str(); *p; p++)
			code += morse_codes[*p];
		context_words[word] = code;
	}
#ifdef DEBUG
	for (map<string, string>::const_iterator i = context_words.begin(); i != context_words.end(); ++i)
		cout << i->first << ' ' << i->second << endl;
#endif
	while (true) {
		string code;
		cin >> code;
		if (code == "*")
			break;
		print_word(code);
	}
	return 0;
}

