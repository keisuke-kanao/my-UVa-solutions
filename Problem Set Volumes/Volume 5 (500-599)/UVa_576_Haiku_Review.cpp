
/*
	UVa 576 - Haiku Review

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_576_Haiku_Review.cpp

	from ACM Mid Central Regionals 1997
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_MidCen/1997/index.html)
*/

#include <iostream>
#include <string>
using namespace std;

int count_syllables(const string& s, size_t position, size_t length)
{
	int nr_syllables = 0;
	bool vowels = false;
	for (size_t i = position, e = position + length; i < e; i++) {
		if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' || s[i] == 'y') {
			if (!vowels) {
				vowels = true;
				nr_syllables++;
			}
		}
		else
			vowels = false;
	}
	return nr_syllables;
}

int main()
{
	while (true) {
		string line;
		getline(cin, line);
		if (line == "e/o/i")
			break;
		size_t p = line.find('/');
		size_t q = line.find('/', p + 1);
		char c;
		if (count_syllables(line, 0, p) != 5)
			c = '1';
		else if (count_syllables(line, p + 1, q - p - 1) != 7)
			c = '2';
		else if (count_syllables(line, q + 1, line.length() - q - 1) != 5)
			c = '3';
		else
			c = 'Y';
		cout << c << endl;
	}
	return 0;
}

