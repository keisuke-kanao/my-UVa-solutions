
/*
	UVa 397 - Equation Elation

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_397_Equation_Elation.cpp

	from ACM Mid-Central Regionals, 1996
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_MidCen/1996/index.html)
*/

#include <iostream>
#include <sstream>
#include <string>
#include <deque>
#include <stack>
#include <cctype>
using namespace std;

enum {type_operator, type_operand};
enum {multiply, divide, add, subtract};

struct op {
	int type_;
	int value_;

	op() {}
	op(int type, int value) : type_(type), value_(value) {}

	string to_string() const {
		ostringstream oss;
		if (type_ == type_operator) {
			switch (value_) {
			case multiply:
				oss << '*'; break;
			case divide:
				oss << '/'; break;
			case add:
				oss << '+'; break;
			case subtract:
				oss << '-'; break;
			}
		}
		else
			oss << value_;
		return oss.str();
	}

#ifdef DEBUG
	void print() const {
		if (type_ == type_operator) {
			switch (value_) {
			case multiply:
				cout << '*'; break;
			case divide:
				cout << '/'; break;
			case add:
				cout << '+'; break;
			case subtract:
				cout << '-'; break;
			}
		}
		else
			cout << value_;
	}
#endif
};

int read_integer()
{
	int i = 0;
	while (true) {
		char c;
		cin >> c;
		if (!isdigit(c)) {
			cin.unget();
			break;
		}
		i *= 10;
		i += c - '0';
	}
	return i;
}

bool read_equation(deque<op>& infix_ops, string& variable, int& nr_muldiv)
{
	nr_muldiv = 0;
	char c = 0;
	while (cin >> c) {
		if (c == '=') {
			cin >> variable;
			return true;
		}
		if (c == '+' || c == '-') {
			if (infix_ops.empty() || infix_ops.back().type_ == type_operator) { // unary operator
				int sign = (c == '-') ? -1 : 1;
				infix_ops.push_back(op(type_operand, sign * read_integer()));
			}
			else
				infix_ops.push_back(op(type_operator, ((c == '-') ? subtract : add)));
		}
		else if (c == '*') {
			nr_muldiv++;
			infix_ops.push_back(op(type_operator, multiply));
		}
		else if (c == '/') {
			nr_muldiv++;
			infix_ops.push_back(op(type_operator, divide));
		}
		else {
			cin.unget();
			infix_ops.push_back(op(type_operand, read_integer()));
		}
	}
	return false;
}

#ifdef DEBUG
void print_equation(const deque<op>& infix_ops, const string& variable)
{
	for (deque<op>::const_iterator i = infix_ops.begin(), e = infix_ops.end(); i != e; ++i) {
		i->print();
		cout <<  ' ';
	}
	cout << "= " << variable << endl;
}
#endif

void infix_to_postfix(const deque<op>& infix_ops, deque<op>& postfix_ops)
{
	stack<op> st;
	for (deque<op>::const_iterator i = infix_ops.begin(), e = infix_ops.end(); i != e; ++i) {
		if (i->type_ == type_operand)
			postfix_ops.push_back(*i);
		else {
			while (!st.empty()) {
				if ((st.top().value_ == multiply || st.top().value_ == divide) ||
					(i->value_ == add || i->value_ == subtract)) { // stack top operator has equal or higher precedence
					postfix_ops.push_back(st.top());
					st.pop();
				}
				else
					break;
			}
			st.push(*i);
		}
	}
	while (!st.empty()) {
		postfix_ops.push_back(st.top());
		st.pop();
	}
}

void print_infix_equation(const deque<op>& postfix_ops, const string& variable)
{
	stack<string> st;
	for (deque<op>::const_iterator i = postfix_ops.begin(), e = postfix_ops.end(); i != e; ++i) {
		if (i->type_ == type_operand)
			st.push(i->to_string());
		else {
			string sj = st.top(); st.pop();
			string si = st.top(); st.pop();
			st.push(si + " " + i->to_string() + " " + sj);
		}
	}
	cout << st.top() << " = " + variable << endl;
}

void calculate(deque<op>& postfix_ops, int& nr_muldiv)
{
	stack<op> st;
	while (!postfix_ops.empty()) {
		op o = postfix_ops.front();
		postfix_ops.pop_front();
		if (o.type_ == type_operand)
			st.push(o);
		else if (nr_muldiv && (o.value_ == add || o.value_ == subtract))
			st.push(o);
		else {
			op oj = st.top();
			st.pop();
			op oi = st.top();
			st.pop();
			int v;
			switch (o.value_) {
			case multiply:
				nr_muldiv--;
				v = oi.value_ * oj.value_; break;
			case divide:
				nr_muldiv--;
				v = oi.value_ / oj.value_; break;
			case add:
				v = oi.value_ + oj.value_; break;
			case subtract:
				v = oi.value_ - oj.value_; break;
			}
			postfix_ops.push_front(op(type_operand, v));
			break;
		}
	}
	while (!st.empty()) {
		postfix_ops.push_front(st.top());
		st.pop();
	}
}

int main()
{
	while (true) {
		deque<op> infix_ops;
		string variable;
		int nr_muldiv;
		if (!read_equation(infix_ops, variable, nr_muldiv))
			break;
		deque<op> postfix_ops;
		infix_to_postfix(infix_ops, postfix_ops);
		print_infix_equation(postfix_ops, variable);
		do {
			calculate(postfix_ops, nr_muldiv);
#ifdef DEBUG
			print_equation(postfix_ops, variable);
#endif
			print_infix_equation(postfix_ops, variable);
		} while (postfix_ops.size() > 1);
		cout << endl;
	}
	return 0;
}

