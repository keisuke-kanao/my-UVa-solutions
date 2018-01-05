
/*
	UVa 11108 - Tautology

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11108_Tautology.cpp

	from Waterloo local contest, 30 September, 2006, Problem D
		(http://acm.student.cs.uwaterloo.ca/~acm00/060930/data/)
*/

#include <cstdio>
#include <cstring>
#include <cctype>
#include <stack>
using namespace std;

char get_op(stack<char>& st, int variables[], int values)
{
	char op = st.top(); st.pop();
	if (islower(op))
		op = (values & (1 << variables[op - 'p'])) ? 1 : 0;
	return op;
}

bool evaluate(const char wff[], int wlength, int variables[], int values)
{
	stack<char> st;
	char op1, op2;
	for (int i = wlength - 1; i >= 0; i--) {
		switch (wff[i]) {
		case 'K':
			op1 = get_op(st, variables, values), op2 = get_op(st, variables, values);
			st.push(op1 & op2);
			break;
		case 'A':
			op1 = get_op(st, variables, values), op2 = get_op(st, variables, values);
			st.push(op1 | op2);
			break;
		case 'N':
			op1 = get_op(st, variables, values);
			st.push((op1) ? 0 : 1);
			break;
		case 'C':
			op1 = get_op(st, variables, values), op2 = get_op(st, variables, values);
			st.push((op1 == 1 && op2 == 0) ? 0 : 1);
			break;
		case 'E':
			op1 = get_op(st, variables, values), op2 = get_op(st, variables, values);
			st.push((op1 == op2) ? 1 : 0);
			break;
		default:
			st.push(wff[i]);
			break;
		}
	}
	return get_op(st, variables, values) == 1;
}

int main()
{

	while (true) {
		const int nr_chars_max = 100;
		char wff[nr_chars_max + 1];
		scanf("%s", wff);
		if (wff[0] == '0')
			break;
		int variables['t' - 'p' + 1];
		memset(variables, -1, sizeof(variables));
		int length = strlen(wff), nr_variables = 0;
		for (int i = 0; i < length; i++)
			if (islower(wff[i])) {
				int j = wff[i] - 'p';
				if (variables[j] == -1)
					variables[j] = nr_variables++;
			}
		bool tautology = true;
		for (int i = 0, j = 1 << nr_variables; i < j && tautology; i++)
			if (!evaluate(wff, length, variables, i))
				tautology = false;
		puts((tautology) ? "tautology" : "not");
	}
	return 0;
}

