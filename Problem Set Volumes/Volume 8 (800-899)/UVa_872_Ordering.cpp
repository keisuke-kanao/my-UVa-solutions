
/*
	UVa 872 - Ordering

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_872_Ordering.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstring>
using namespace std;

const int nr_letters = 26, nr_variables_max = 20;
bool forbiddens[nr_letters][nr_letters];
	// forbiddens[i][j] is true if there is a constraint ('A' + i) < ('A' + j)
int variables[nr_variables_max], orders[nr_variables_max];
bool visited[nr_variables_max];

void ordering(int n, int oi, int& nr_printed)
{
	if (oi == n) {
		nr_printed++;
		for (int i = 0; i < n; i++) {
			if (i)
				cout << ' ';
			cout << static_cast<char>('A' + orders[i]);
		}
		cout << endl;
	}
	else {
		for (int i = 0; i < n; i++)
			if (!visited[i]) {
				int j;
				for (j = 0; j < oi; j++)
					if (forbiddens[orders[j]][variables[i]])
						break;
				if (j == oi) { // no constraints
					visited[i] = true;
					orders[oi] = variables[i];
					ordering(n, oi + 1, nr_printed);
					visited[i] = false;
				}
			}
	}
}

int main()
{
	string line;
	istringstream iss;
	getline(cin, line);
	iss.str(line);
	int nr_cases;
	iss >> nr_cases;
	iss.clear();
	while (nr_cases--) {
		getline(cin, line); // skip a blank line
		getline(cin, line);
		int nr_variables = 0;
		iss.str(line);
		char c;
		while (iss >> c)
			variables[nr_variables++] = c - 'A';
		sort(variables, variables + nr_variables);
		iss.clear();
		memset(forbiddens, 0, sizeof(forbiddens));
		getline(cin, line);
		iss.str(line);
		string s;
		while (iss >> s)
			forbiddens[s[2] - 'A'][s[0] - 'A'] = true;
		iss.clear();
		memset(visited, 0, sizeof(visited));
		int nr_printed = 0;
		ordering(nr_variables, 0, nr_printed);
		if (!nr_printed)
			cout << "NO\n";
		if (nr_cases)
			cout << endl;
	}
	return 0;
}

