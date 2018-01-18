
/*
	6.6.1 How Many Fibs?
	PC/UVa IDs: 110601/10183, Popularity: B, Success rate: average Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10183_How_Many_Fibs.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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

int compare_number(const string& n, const string& m)
{
	// comparet the number represented by n with the number represented by m
	if (n.length() > m.length())
		return 1;
	else if (n.length() < m.length())
		return -1;
	else {
		for (int i = 0; i < n.length(); i++) {
			if (n[i] > m[i])
				return 1;
			else if (n[i] < m[i])
				return -1;
		}
		return 0;
	}
}

bool compare_n(const string& i, const string& j)
{
	return compare_number(i, j) < 0;
}

int generate_fibs(vector<string>& fibs)
{
	const string f_max = "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
		// 10~102
	string f1 = "1", f2 = "2";
	fibs.push_back(f1); fibs.push_back(f2);
	while (true) {
		string f = add_number(f1, f2);
		if (compare_number(f, f_max) > 0)
			break;
		fibs.push_back(f);
		f1 = f2; f2 = f;
	}

	return fibs.size();
}

int how_many_fibs(const vector<string>& fibs, string a, string b)
{
	vector<string>::const_iterator i_min = lower_bound(fibs.begin(), fibs.end(), a, compare_n);
	vector<string>::const_iterator i_max = upper_bound(fibs.begin(), fibs.end(), b, compare_n);
	int nr_fibs = distance(i_min, i_max);
	if (nr_fibs < 0)
		nr_fibs = 0;
	return nr_fibs;
}

int main(int /* argc */, char ** /* argv */)
{
	vector<string> fibs;
	generate_fibs(fibs);
#ifdef DEBUG
	cout << fibs.size() << " fibs generated\n";
	for (int i = 0; i < 8; i++)
		cout << fibs[i] << endl;
	cout << "...\n";
	for (int i = fibs.size() - 4; i < fibs.size(); i++)
		cout << fibs[i] << endl;
#endif
	string a, b;
	while (cin >> a >> b) {
		if (a == "0" && b == "0")
			break;
		cout << how_many_fibs(fibs, a, b) << endl;
	}
	return 0;
}

