
/*
	UVa 12243 - Flowers Flourish from France

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12243_Flowers_Flourish_from_France.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

int main()
{
	while (true) {
		string line;
		getline(cin, line);
		if (line[0] == '*')
			break;
		istringstream iss(line);
		string word;
		iss >> word;
		int letter = tolower(word[0]);
		bool tautogram = true;
		while (tautogram && iss >> word)
			if (tolower(word[0]) != letter)
				tautogram = false;
		cout << ((tautogram) ? "Y\n" : "N\n");
	}
	return 0;
}

