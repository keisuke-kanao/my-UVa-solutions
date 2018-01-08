
/*
	UVa 11234 - Expressions

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11234_Expressions.cpp

	from University of Ulm Local Contest 2007 Problem E
		(http://www.informatik.uni-ulm.de/acm/Locals/2007/)
*/

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include <cctype>
using namespace std;

struct nr_or_op { // number or operator
	int i_; 
	int next_;
	int op_; // 0 for number, 1for operator
	int depth_; // nesting depth of the expression
};

const int nr_or_ops_max = 10000;

nr_or_op nr_or_ops[nr_or_ops_max];

bool compare_nr_or_op(const nr_or_op& i, const nr_or_op& j)
{
	if (i.depth_ > j.depth_)
		return true;
	else if (i.depth_ < j.depth_)
		return false;
	else {
		if (i.i_ > j.i_)
			return true;
		else
			return false;
	}
}

int main()
{
	int t;
	cin >> t;
	while (t--) {
		string es;
		cin >> es;
		stack<int> st;
		int length = es.length();
		for (int i = 0; i < length; i++) {
			nr_or_ops[i].i_ = i;
			if (islower(es[i])) { // number
				nr_or_ops[i].next_ = -1;
				nr_or_ops[i].op_ = 0; nr_or_ops[i].depth_ = 0;
				st.push(i);
			}
			else { // operator
				nr_or_ops[i].op_ = 1; nr_or_ops[i].depth_ = 0;
				int right = st.top(); // right operand
				st.pop();
				int left = st.top(); // left operand
				st.pop();
				nr_or_ops[left].depth_++;
				int j;
				for (j = left; nr_or_ops[j].next_ != -1; j = nr_or_ops[j].next_)
					nr_or_ops[nr_or_ops[j].next_].depth_++;
				nr_or_ops[j].next_ = i;
				nr_or_ops[i].next_ = right;
				nr_or_ops[right].depth_++;
				for (j = nr_or_ops[right].next_; j != -1; j = nr_or_ops[j].next_)
					nr_or_ops[j].depth_++;
				st.push(left);
			}
		}
#ifdef DEBUG
		for (int i = st.top(); i != -1; i = nr_or_ops[i].next_) 
			cout << es[nr_or_ops[i].i_] << '(' << nr_or_ops[i].depth_<< ") ";
		cout << endl;
#endif
		sort(nr_or_ops, nr_or_ops + length, compare_nr_or_op);
#ifdef DEBUG
		for (int i = 0; i < length; i++) 
			cout << es[nr_or_ops[i].i_] << '(' << nr_or_ops[i].depth_<< ") ";
		cout << endl;
#endif
		for (int i = 0; i < length; i++)
			cout << es[nr_or_ops[i].i_];
		cout << endl;
	}
	return 0;
}

