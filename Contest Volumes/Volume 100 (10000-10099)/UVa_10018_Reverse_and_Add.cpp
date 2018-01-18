
/*
	5.9.2 Reverse and Add
	PC/UVa IDs: 110502/10018, Popularity: A, Success rate: low Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10018_Reverse_and_Add.cpp
*/

#include <iostream>
#include <string>
using namespace std;

string reverse_and_add(const string& n)
{
	string s;
	int length = n.length() - 1;
	int c = 0;
	for (int i = length; i >= 0; i--) {
		int j = (n[i] - '0') + (n[length - i] - '0') + c;
		if (j >= 10)
			c = 1;
		else
			c = 0;
		s.insert(s.begin(), j % 10 + '0');
	}
	if (c)
		s.insert(s.begin(), '1');
	return s;
}

bool is_palindrome(const string& n)
{
	int length = n.length();
	for (int i = 0; i < length / 2; i++)
		if (n[i] != n[length - i - 1])
			return false;
	return true;
}

int main(int /* argc */, char** /* argv */)
{
	// read the number of test cases
	int cases;
	cin >> cases;
	while (cases--) {
		// read an integer as a string
		string n;
		cin >> n;
		int i = 0;
		do {
			n = reverse_and_add(n);
			i++;
		} while (!is_palindrome(n));
		cout << i << ' ' << n << endl;
	}
	return 0;
}

