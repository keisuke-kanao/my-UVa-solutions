
/*
	UVa 333 - Recognizing Good ISBNs

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_333_Recognizing_Good_ISBNs.cpp

	from ACM  North Central Regionals 1994
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_NorthCen/1994/index.html)

	Note that almost all of the discussions about this problem, including the one at "Method to Solve", 
	are WRONG.
*/

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool recognize_ISBN(const string& s, string& isbn)
{
	int i, j, l = s.length();
	for (i = 0; i < l; i++)
		if (!isspace(s[i]))
			break;
	if (i == l)
		return false;
	for (j = l - 1; ; j--)
		if (!isspace(s[j]))
			break;
	isbn = s.substr(i, j - i + 1);

	const int nr_digits = 10;
	int n = 0, sum = 0, s1[nr_digits];
	for (i = 0, l = isbn.length(); i < l; i++) {
		char c = isbn[i];
		if (isdigit(c) && n < nr_digits || c == 'X' && n == nr_digits - 1) {
			sum += (c == 'X') ? 10 : c - '0';
			s1[n++] = sum;
		}
		else if (c != '-')
			return false;
	}
	if (n < nr_digits)
		return false;
	for (i = 0, sum = 0; i < nr_digits; i++)
		sum += s1[i];
	return (sum % 11) ? false : true;
}

int main()
{
	string s;
	while (getline(cin, s)) {
		string isbn;
		bool result = recognize_ISBN(s, isbn);
		cout << isbn << ((result) ? " is correct.\n" : " is incorrect.\n");
	}
	return 0;
}

