
/*
	UVa 486 - English-Number Translator

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_486_English-Number_Translator.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <map>
using namespace std;

const pair<string, int> number_words_[] = {
	make_pair("negative", -1),
	make_pair("zero", 0), make_pair("one", 1), make_pair("two", 2), make_pair("three", 3),
	make_pair("four", 4), make_pair("five", 5), make_pair("six", 6), make_pair("seven", 7),
	make_pair("eight", 8), make_pair("nine", 9), make_pair("ten", 10),
	make_pair("eleven", 11), make_pair("twelve", 12), make_pair("thirteen", 13), make_pair("fourteen", 14),
	make_pair("fifteen", 15), make_pair("sixteen", 16), make_pair("seventeen", 17), make_pair("eighteen", 18),
	make_pair("nineteen", 19), make_pair("twenty", 20), make_pair("thirty", 30), make_pair("forty", 40),
	make_pair("fifty", 50), make_pair("sixty", 60), make_pair("seventy", 70), make_pair("eighty", 80),
	make_pair("ninety", 90), make_pair("hundred", 100), make_pair("thousand", 1000), make_pair("million", 1000000)
};

int main()
{
	map<string, int> number_words;
	for (size_t i = 0, e = sizeof(number_words_) / sizeof(pair<string, int>); i < e; i++)
		number_words.insert(number_words_[i]);
	string line;
	while (getline(cin, line)) {
		istringstream iss(line);
		int number = 0, sign = 1, pn = -1;
		string nw;
		while (iss >> nw) {
			int n = number_words[nw];
			if (n == -1)
				sign = -1;
			else if (n >= 100) {
				if (pn == -1)
					pn = n;
				else
					pn *= n;
				if (n >= 1000) {
					number += pn;
					pn = 0;
				}
			}
			else {
				if (pn == -1)
					pn = n;
				else
					pn += n;
			}
		}
		if (pn)
			number += pn;
		cout << sign * number << endl;
	}
	return 0;
}

