
/*
	UVa 494 - Kindergarten Counting Game

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_494_Kindergarten_Counting_Game.cpp
*/

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main(int /* argc */, char** /* argv */)
{
	string s;
	while (getline(cin, s)) {
		int nr_words = 0;
		bool in_word = false;
		for (int i = 0, l = s.length(); i < l; i++) {
			if (isalpha(s[i])) {
				if (!in_word) {
					in_word = true;
					nr_words++;
				}
			}
			else
				in_word = false;
		}
		cout << nr_words << endl;
	}
	return 0;
}

