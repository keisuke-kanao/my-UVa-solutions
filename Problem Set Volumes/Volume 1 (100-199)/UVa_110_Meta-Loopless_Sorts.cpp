
/*
	UVa 110 - Meta-Loopless Sorts

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_110_Meta-Loopless_Sorts.cpp
*/

#include <iostream>
#include <algorithm>
#include <cstring>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int n_max = 8;

void print_indent(int indent)
{
	for (int i = 0; i < 2 * indent; i++)
		cout << ' ';
}

void writeln(int n, char variables[])
{
	cout << "writeln(";
	for (int i = 0; i < n; i++)
		cout << variables[i] << ((i == n - 1) ? ')' : ',');
	cout << endl;
}

void permutate_variables(int m, int n, char variables[])
{
	print_indent(m);
	cout << "if " << variables[m - 1] << " < " << variables[m] << " then\n";
	if (m + 1 < n)
		permutate_variables(m + 1, n, variables);
	else {
		print_indent(m + 1);
		writeln(n, variables);
	}
	char vars[n_max];
	memcpy(vars, variables, n);
	for (int i = m; i > 0; i--) {
		swap(vars[i - 1], vars[i]);
		print_indent(m);
		if (i > 1)
			cout << "else if " << vars[i - 2] << " < " << vars[i - 1] << " then\n";
		else
			cout << "else\n";
		if (m + 1 < n)
			permutate_variables(m + 1, n, vars);
		else {
			print_indent(m + 1);
			writeln(n, vars);
		}
	}
}

int main()
{
	int m;
	cin >> m;
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	while (m--) {
		int n;
		cin >> n;
		char variables[n_max];
		for (int i = 0; i < n; i++)
			variables[i] = static_cast<char>(i + 'a');
		cout << "program sort(input,output);\nvar\n";
		for (int i = 0; i < n; i++)
			cout << variables[i] << ((i == n - 1) ? ' ' : ',');
		cout << ": integer;\nbegin\n  readln(";
		for (int i = 0; i < n; i++)
			cout << variables[i] << ((i == n - 1) ? ')' : ',');
		cout << ";\n";
		if (n == 1)
			cout << "  writeln(a)\n";
		else
			permutate_variables(1, n, variables);
		cout << "end.\n";
		if (m)
			cout << endl;
	}
#ifdef __ELAPSED_TIME__
		cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

