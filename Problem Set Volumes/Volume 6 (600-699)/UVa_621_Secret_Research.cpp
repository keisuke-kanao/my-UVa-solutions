
/*
	UVa 621 - Secret Research

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_621_Secret_Research.cpp
*/

#include <iostream>
#include <string>
using namespace std;

char decrypt_digits(const string s)
{
	if (s == "1" || s == "4" || s == "78")
		return '+'; // positive result
	size_t length = s.length();
	if (length >= 2 && s[length - 2] == '3' && s[length - 1] == '5')
		return '-'; // negative result
	else if (length >= 2 && s[0] == '9' && s[length - 1] == '4')
		return '*'; // experiment failed
	else if (length >= 3 && s[0] == '1' && s[1] == '9' && s[2] == '0')
		return '?'; // experiment not completed
	else
		return '\0';
}

int main()
{
	int n;
	cin >> n;
	while (n--) {
		string s;
		cin >> s;
		char c = decrypt_digits(s);
		if (c)
			cout << c << endl;
	}
	return 0;
}

