
/*
	UVa 10945 - Mother bear

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10945_Mother_bear.cpp
*/

#include <iostream>
#include <string>
#include <cctype>
using namespace std;


bool is_palindrome(const char* s, int length)
{
	for (int i = 0, j = length - 1; i < j; i++, j--)
		if (s[i] != s[j])
			return false;
	return true;
}

int main()
{
	while (true) {
		string s;
		getline(cin, s);
		if (s == "DONE")
			break;
		int sl = s.length();
		char* t = new char[sl];
		int tl = 0;
		for (int i = 0; i < sl; i++)
			if (isalpha(s[i]))
				t[tl++] = tolower(s[i]);
		cout << ((is_palindrome(t, tl)) ? "You won't be eaten!\n" : "Uh oh..\n");
		delete[] t;
	}
	return 0;
}

