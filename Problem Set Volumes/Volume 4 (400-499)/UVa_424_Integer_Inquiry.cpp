
/*
	UVa 424 - Integer Inquiry

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_424_Integer_Inquiry.cpp
*/

#include <iostream>
#include <string>
using namespace std;

string add_number(const string& n, const string& m)
{
	// add the number represented by m to the number represented by n
	string result;
	int i, j, carry;
	for (i = n.length() - 1, j = m.length() - 1, carry = 0; i >= 0 || j >= 0; i--, j--) {
		int k = (i >= 0) ? n[i] - '0' : 0;
		int l = (j >= 0) ? m[j] - '0' : 0;
		int p = k + l + carry;
		if (p > 9) {
			p -= 10;
			carry = 1;
		}
		else
			carry = 0;
		result.insert(result.begin(), p + '0');
	}
	if (carry)
		result.insert(result.begin(), '1');
	return result;
}

int main()
{
	const string zero("0");
	string sum("0");
	while (true) {
		string n;
		cin >> n;
		if (n == zero)
			break;
		sum = add_number(sum, n);
	}
	cout << sum << endl;
	return 0;
}

