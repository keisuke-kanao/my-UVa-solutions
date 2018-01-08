
/*
	UVa 673 - Parentheses Balance

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_673_Parentheses_Balance.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <stack>
using namespace std;

int main()
{
	string line;
	istringstream iss;
	getline(cin, line);
	iss.str(line);
	int n;
	iss >> n;
	iss.clear();
	while (n--) {
		getline(cin, line);
		stack<char> ps;
		bool correct = true;
		for (const char* p = line.c_str(); *p && correct; p++) {
			switch (*p) {
			case '(': case '[':
				ps.push(*p); break;
			case ')':
				if (ps.empty() || ps.top() != '(')
					correct = false;
				else
					ps.pop();
				break;
				ps.push(*p); break;
			case ']':
				if (ps.empty() || ps.top() != '[')
					correct = false;
				else
					ps.pop();
				break;
			default:
				break;
			}
		}
		if (correct && !ps.empty())
			correct = false;
		cout << ((correct) ? "Yes\n" : "No\n");
	}
	return 0;

}

