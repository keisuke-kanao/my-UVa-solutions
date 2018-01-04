
/*
	UVa 325 - Identifying Legal Pascal Real Constants

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_325_Identifying_Legal_Pascal_Real_Constants.cpp

	from ACM  North Central Regionals 1993
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_NorthCen/1993/prob_b.html)
*/

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool parse_fractional_digits(const string& s, bool has_exponent_part)
{
	int i, j, length = s.length();
	if (!length)
		return false;
	i = 0;
	if (s[i] == '+' || s[i] == '-') {
		if (length == 1)
			return false;
		i++;
	}
	int di = -1;
	for (j = i; j < length; j++) {
		if (s[j] == '.') {
			if (j == i)
				return false; // no digits before the decimal ponit
			else if (di != -1)
				return false;
			else {
				di = j;
				i = j + 1;
			}
		}
		else if (!isdigit(s[j]))
			return false;
	}
	if (di == -1) // no decimal point
		return has_exponent_part;
	else
		return (j == i) ? false : true;
}

bool parse_exponent_digits(const string& s)
{
	int i, length = s.length();
	if (!length)
		return false;
	i = 0;
	if (s[i] == '+' || s[i] == '-') {
		if (length == 1)
			return false;
		i++;
	}
	for ( ; i < length; i++)
		if (!isdigit(s[i]))
			return false;
	return true;
}

bool is_legal_pascal_real_constants(const string& s, string& sr)
{
	int i, j, length = s.length();
	// remove spaces
	for (i = 0; i < length; i++)
		if (!isspace(s[i]))
			break;
	if (i == length)
		return false;
	for (j = length - 1; ; j--)
		if (!isspace(s[j]))
			break;
	sr = s.substr(i, j - i + 1);
	int p = sr.find('e');
	if (p == string::npos)
		p = sr.find('E');
	bool result;
	if (p == string::npos) // no exponent part
		result = parse_fractional_digits(sr, false);
	else {
		result = parse_fractional_digits(sr.substr(0, p), true);
		if (result)
			result = parse_exponent_digits(sr.substr(p + 1));
	}
	return result;
}

int main()
{
	while (true) {
		string s;
		getline(cin, s);
		if (s.length() == 1 && s[0] == '*')
			break;
		string sr;
		bool result = is_legal_pascal_real_constants(s, sr);
		cout << sr << ((result) ? " is legal.\n" : " is illegal.\n");
	}
	return 0;
}

