
/*
	UVa 10700 - Camel trading

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10700_Camel_trading.cpp

	An accepted solution.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <list>
using namespace std;

const int nr_n_or_op_max = 23;

struct n_or_op
{
	bool is_op_; // true for operator, false for number
	union {
		long long n_;
		char op_;
	};
};

long long calculate_min_max(char op, int nr_n_or_ops, const n_or_op n_or_ops[])
{
	list<n_or_op> ln_or_ops(n_or_ops, n_or_ops + nr_n_or_ops);
	long long n;
	// first, apply the operator of preference
	for (list<n_or_op>::iterator i = ln_or_ops.begin(), j = ln_or_ops.begin(), e = ln_or_ops.end();
		j != e; ++j) {
		if (j->is_op_) {
			if (j->op_ == op) {
				++j;
				i = j = ln_or_ops.erase(i, j);
				if (op == '+')
					j->n_ += n;
				else
					j->n_ *= n;
				n = j->n_;
			}
		}
		else {
			i = j;
			n = j->n_;
		}
	}
	// second, apply another operator
	op = (op == '+') ? '*' : '+';
	for (list<n_or_op>::iterator i = ln_or_ops.begin(), j = ln_or_ops.begin(), e = ln_or_ops.end();
		j != e; ++j) {
		if (j->is_op_) {
			++j;
			i = j = ln_or_ops.erase(i, j);
			if (op == '+')
				j->n_ += n;
			else
				j->n_ *= n;
		}
		n = j->n_;
	}
	return ln_or_ops.begin()->n_;
}

int main()
{
	int nr_cases;
	cin >> nr_cases;
	string s;
	getline(cin, s); // skip '\n'
	while (nr_cases--) {
		getline(cin, s);
		istringstream iss(s);
		n_or_op n_or_ops[nr_n_or_op_max];
		int nr_n_or_ops = 0;
		while (iss >> n_or_ops[nr_n_or_ops].n_) {
			n_or_ops[nr_n_or_ops++].is_op_ = false;
			if (iss >> n_or_ops[nr_n_or_ops].op_)
				n_or_ops[nr_n_or_ops++].is_op_ = true;
		}
		cout << "The maximum and minimum are " << calculate_min_max('+', nr_n_or_ops, n_or_ops) <<
			" and " << calculate_min_max('*', nr_n_or_ops, n_or_ops) << ".\n";
	}
	return 0;
}

