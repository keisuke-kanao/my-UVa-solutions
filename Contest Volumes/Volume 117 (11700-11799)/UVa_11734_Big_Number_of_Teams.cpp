
/*
	UVa 11734 - Big Number of Teams will Solve This

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11734_Big_Number_of_Teams.cpp
*/

#include <iostream>
#include <string>
using namespace std;

int verdict(const char* answer, const char* expected)
{
	bool extra_spaces = false;
	while (*answer && *expected) {
		char a = *answer, e = *expected;
		if (isspace(a)) {
			if (isspace(e))
				expected++;
			else
				extra_spaces = true;
			answer++;
		}
		else {
			if (a != e)
				return -1;
			answer++; expected++;
		}
	}
	if (*expected)
		return -1;
	else if (*answer) {
		while (*answer) {
			if (isspace(*answer))
				answer++;
			else
				return -1;
		}
		return 0;
	}
	else
		return (extra_spaces) ? 0 : 1;
}

int main()
{
	int t;
	cin >> t;
	string s;
	getline(cin, s);
	for (int case_nr = 1; case_nr <= t; case_nr++) {
		string answer, expected;
		getline(cin, answer);
		getline(cin, expected);
		int result = verdict(answer.c_str(), expected.c_str());
		cout << "Case " << case_nr << ": ";
		if (result == 1)
			cout << "Yes\n";
		else if (!result)
			cout << "Output Format Error\n";
		else
			cout << "Wrong Answer\n";
	}
	return 0;
}

