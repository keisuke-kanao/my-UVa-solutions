
/*
	UVa 565 - Pizza Anyone?

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_565_Pizza_Anyone.cpp

	from 1997 ACM South Central USA Programming Contest Problem #1
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_SouthCen/1997/Pizza.html)
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#ifdef DEBUG
#include <cassert>
#endif
using namespace std;

const int nr_topping_constraints_default = 12;

int nr_topping_constraints, nr_topping_constraints_max = nr_topping_constraints_default;

struct topping_constraint {
	int nr_; // number of constraints
	unsigned int constraints_;

	topping_constraint() : nr_(0), constraints_(0) {}
/*
	Each constraint for a topping is represented the consecutive two bits, where 
	the lower bit is for without the topping and the higher bit is for with the topping.
*/
	bool operator<(const topping_constraint& tp) const {return nr_ < tp.nr_;}
};

vector<topping_constraint> topping_constraints(nr_topping_constraints_max);

void parse_topping_constraint(const char* s, topping_constraint& tc)
{
	tc.nr_ = 0; tc.constraints_ = 0;
	do {
		bool with_topping = *s++ == '+';
		int shift = (*s++ - 'A') * 2;
		unsigned int current = (tc.constraints_ >> shift) & 3;
		if (with_topping) {
			if (current == 1) { // without the topping
				tc.nr_--;
				tc.constraints_ &= ~(1 << shift);
			}
			else if (!current) {
				tc.nr_++;
				tc.constraints_ |= 2 << shift;
			}
		}
		else {
			if (current == 2) { // with the topping
				tc.nr_--;
				tc.constraints_ &= ~(2 << shift);
			}
			else if (!current) {
				tc.nr_++;
				tc.constraints_ |= 1 << shift;
			}
		}
	} while (*s != ';');
}

bool accept_constraints(int tci, unsigned int constraints, unsigned int& accepted_constraints)
{
	if (tci == nr_topping_constraints) {
		accepted_constraints = constraints;
		return true;
	}
/*
	From topping_constraints[tci], add a topping constraint that is not inconsistent with 
	the constraints that have already been set in constraints
*/
	topping_constraint& tc = topping_constraints[tci];
	unsigned int c = tc.constraints_;
	if (c & constraints) // at least one topping constraint has already been satisfied
		return accept_constraints(tci + 1, constraints, accepted_constraints);
	bool successful = false;
	unsigned int mask = 3;
	for (int nr = tc.nr_; nr; mask <<= 2) {
		unsigned int current = constraints & mask, request = c & mask;
		if (request) {
			nr--;
			if (!current) { // a topping constraint has yet not been set
				constraints |= request;
				successful = accept_constraints(tci + 1, constraints, accepted_constraints);
				constraints &= ~request;
			}
			if (successful)
				break;
		}
	}
	return successful;
}

void print_toppings(unsigned int constraints)
{
	cout << "Toppings:";
	bool printed = false;
	for (int i = 0; constraints; i++, constraints >>= 2)
		if (constraints & 2) { // with a topping
			if (!printed) {
				printed = true;
				cout << ' ';
			}
			cout << static_cast<char>('A' + i);
		}
	cout << '\n';
}

#ifdef DEBUG
bool verify_constraints(unsigned int constraints)
{
	for (int i = 0; i < nr_topping_constraints; i++) {
		topping_constraint& tc = topping_constraints[i];
		unsigned int c = tc.constraints_;
		unsigned int mask = 3;
		bool satisfied = false;
		for (int nr = tc.nr_; nr; mask <<= 2) {
			unsigned int current = constraints & mask, request = c & mask;
			if (request) {
				nr--;
				if (current == request) {
					satisfied = true; break;
				}
			}
		}
		if (!satisfied)
			return false;
	}
	return true;
}
#endif

int main()
{
	string s;
	while (cin >> s) {
		nr_topping_constraints = 0;
		do {
			if (nr_topping_constraints >= nr_topping_constraints_max) {
				nr_topping_constraints_max++;
				topping_constraints.push_back(topping_constraint());
			}
			parse_topping_constraint(s.c_str(), topping_constraints[nr_topping_constraints]);
			nr_topping_constraints++;
			cin >> s;
		} while (s[0] != '.');
		// sort the topping constraints in ascending order of their number of constraints
		sort(topping_constraints.begin(), topping_constraints.begin() + nr_topping_constraints);
		unsigned int accepted_constraints = 0;
		if (accept_constraints(0, 0, accepted_constraints)) {
			print_toppings(accepted_constraints);
#ifdef DEBUG
			assert(verify_constraints(accepted_constraints));
#endif
		}
		else
			cout << "No pizza can satisfy these requests.\n";
	}
	return 0;
}

