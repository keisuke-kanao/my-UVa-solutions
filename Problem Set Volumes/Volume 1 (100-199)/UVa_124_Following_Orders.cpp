
/*
	UVa 124 - Following Orders

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_124_Following_Orders.cpp

	An accepted solution.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

bool is_ordered(int n, int i, const vector<char>& variables, const vector< vector<int> >& constraints, vector<bool>& used)
{
	int j = variables[i] - 'a';
	for (int k = 0; k < n; k++)
		if (!used[k] && constraints[j][variables[k] - 'a'] > 0)
			return false;
	return true;
}

void follow_orders(int n, int i, const vector<char>& variables, const vector< vector<int> >& constraints,
	vector<bool>& used, vector<char>& order)
{
	if (i == n) {
		for (int i = 0; i < n; i++)
			cout << order[i];
		cout << endl;
	}
	else {
		for (int j = 0; j < n; j++)
			if (!used[j] && is_ordered(n, j, variables, constraints, used)) {
				used[j] = true;
				order[i] = variables[j];
				follow_orders(n, i + 1, variables, constraints, used, order);
				used[j] = false;
			}
	}
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	bool printed = false;
	string line;
	istringstream iss;
	while (getline(cin, line)) {
		if (printed)
			cout << endl;
		else
			printed = true;
		iss.str(line);
		vector<char> variables;
		char c, d;
		while (iss >> c)
			variables.push_back(c);
		iss.clear();
		sort(variables.begin(), variables.end());
		getline(cin, line);
		iss.str(line);
		const int nr_letters = 26;
		vector< vector<int> > constraints(nr_letters, vector<int>(nr_letters, 0));
		// constraints[i][j] is 1 if i + 'a' > j + 'a', -1 if i + 'a' < j + 'a', 0 if undefined
		while (iss >> c >> d) {
			int i = c - 'a', j = d - 'a';
			constraints[i][j] = -1; constraints[j][i] = 1;
		}
		iss.clear();
		int n = variables.size();
		vector<bool> used(n, false);
		vector<char> order(n);
		follow_orders(n, 0, variables, constraints, used, order);
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

