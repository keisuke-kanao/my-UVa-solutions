
/*
	UVa 401 - Palindromes

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_401_Palindromes.cpp
*/

#include <iostream>
#include <string>
using namespace std;

bool is_palindrome(const string& s)
{
	for (int i = 0, j = s.length() - 1; i < j; i++, j--)
		if (s[i] != s[j])
			return false;
	return true;
}

bool is_mirrored(const string& s)
{
	const char reverse_chars[] = { // reverse_chars[c - '1'] is a reverse character for an valid character c
		'1', 'S', 'E', -1, 'Z', -1, -1, '8', -1, // '1' - '9'
		-1, -1, -1, -1, -1, -1, -1, // not used
		'A', -1, -1, -1, '3', -1, -1, 'H', 'I', 'L', -1, 'J', // 'A' - 'L'
		'M', -1, 'O', -1, -1, -1, '2', 'T', 'U', 'V', 'W', 'X', // 'M' - 'X'
		'Y', '5' // 'Y' - 'Z'
	};

	for (int i = 0, j = s.length() - 1; i <= j; i++, j--)
		if (reverse_chars[s[i] - '1'] != s[j])
			return false;
	return true;
}

int main(int /* argc */, char** /* argv */)
{
	string s;
	while (cin >> s) {
		int palindrome = is_palindrome(s);
		int mirrored = is_mirrored(s);
		const char* messages[] = {
			" -- is not a palindrome.\n\n", " -- is a regular palindrome.\n\n",
			" -- is a mirrored string.\n\n", " -- is a mirrored palindrome.\n\n"
		};
		cout << s << messages[palindrome + (mirrored << 1)];
	}
}

