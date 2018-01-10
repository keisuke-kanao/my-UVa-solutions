
/*
	UVa 10344 - 23 Out of 5

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10344_23_Out_of_5.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int nr_variables = 5, nr_operators = 4;

bool calculate_expression(int nr_applied, char operators[], const int variables[])
{
	if (nr_applied == nr_operators) {
		int result = variables[0];
		for (int i = 0; i < nr_operators; i++) {
			int variable = variables[i + 1];
			switch (operators[i]) {
			case '+':
				result += variable; break;
			case '-':
				result -= variable; break;
			case '*':
				result *= variable; break;
			}
		}
#ifdef DEBUG
		if (result == 23) {
			cout << "(((" << variables[0] << ' ' << operators[0] << ' ' << variables[1] << ")) " <<
				operators[1] << ' ' << variables[2] << ")) " << operators[2] << ' ' << variables[3] << ")) " <<
				operators[3] << ' ' << variables[4] << endl;
			return true;
		}
		else
			return false;
#else
		return result == 23;
#endif
	}
	else {
		const char ops[] = {'+', '-', '*'};
		for (int i = 0; i < sizeof(ops) / sizeof(char); i++) {
			operators[nr_applied] = ops[i];
			if (calculate_expression(nr_applied + 1, operators, variables))
				return true;
		}
		return false;
	}
}

int main()
{
	while (true) {
		int variables[nr_variables];
		cin >> variables[0] >> variables[1] >> variables[2] >> variables[3] >> variables[4];
		if (!variables[0] && !variables[1] && !variables[2] && !variables[3] && !variables[4])
			break;
		sort(variables, variables + nr_variables);
		bool possible = false;
		do {
#ifdef DEBUG
			for (int i = 0; i < nr_variables; i++)
				cout << ' ' << variables[i];
			cout << endl;
#endif
			char operators[nr_operators];
				// operators[i] is the i-th operator applied to the expression ('+' or '-' or '*')
			if (possible = calculate_expression(0, operators, variables))
				break;
		} while (next_permutation(variables, variables + nr_variables));
		cout << ((possible) ? "Possible\n" : "Impossible\n");
	}
	return 0;
}

