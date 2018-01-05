
/*
	UVa 10924 - Prime Words

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10924_Prime_Words.cpp
*/

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

bool is_prime(int n)
{
	if (n < 3)
		return true;
	else if (!(n % 2))
		return false;
	else {
		for (int i = 3; i <= static_cast<int>(sqrt(static_cast<double>(n))) + 1; i += 2)
			if (!(n % i))
				return false;
	}
	return true;
}

int main()
{
	string word;
	while (cin >> word) {
		int s = 0;
		for (const char* p = word.c_str(); *p; p++)
			s += (islower(*p)) ? *p - 'a' + 1 : *p - 'A' + 27;
		cout << ((is_prime(s)) ? "It is a prime word.\n" : "It is not a prime word.\n");
	}
	return 0;
}

