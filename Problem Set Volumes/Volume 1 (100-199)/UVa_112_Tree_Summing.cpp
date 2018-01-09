
/*
	UVa 112 - Tree Summing

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_112_Tree_Summing.cpp

	An accepted solution.
*/

#include <iostream>
#ifndef ONLINE_JUDGE
#include <cassert>
#endif
#include <cctype>
using namespace std;

enum {tk_opening_parenthesis, tk_closing_parenthesis, tk_number}; // tokens
enum {ts_false, ts_true, ts_leaf};

int get_token(int& n)
{
	while (true) {
		int c = cin.get();
		if (isspace(c))
			continue;
		if (c == '(')
			return tk_opening_parenthesis;
		else if (c == ')')
			return tk_closing_parenthesis;
		else if (isdigit(c) || c == '-') {
			n = 0;
			int sign = 1;
			while (true) {
				if (c == '-')
					sign = -1;
				else if (isdigit(c)) {
					n *= 10;
					n += c - '0';
				}
				else if (!isspace(c))
					break;
				c = cin.get();
			}
			cin.unget();
			n *= sign;
			return tk_number;
		}
	}
}

int tree_summing(int s, int i)
{
	int n;
	int token = get_token(n);
#ifndef ONLINE_JUDGE
	assert(token == tk_opening_parenthesis);
#endif
	if ((token = get_token(n)) == tk_closing_parenthesis)
		return ts_leaf;
    else {
#ifndef ONLINE_JUDGE
		assert(token == tk_number);
#endif
        s += n;
	}
	int left = tree_summing(s, i), right = tree_summing(s, i);
	token = get_token(n);
#ifndef ONLINE_JUDGE
	assert(token == tk_closing_parenthesis);
#endif
	if (left == ts_leaf && right == ts_leaf) {
		if (s == i)
			return ts_true;
	}
	if (left == ts_true || right == ts_true)
		return ts_true;
	else
		return ts_false;
}

int main()
{
	int i;
	while (cin >> i)
		cout << ((tree_summing(0, i) == ts_true) ? "yes\n" : "no\n");
	return 0;
}

