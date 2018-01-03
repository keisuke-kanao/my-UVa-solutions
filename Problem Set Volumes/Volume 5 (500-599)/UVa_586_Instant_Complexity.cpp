
/*
	UVa 586 - Instant Complexity

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_586_Instant_Complexity.cpp

	from  ACM Western and Southwestern European Regionals 1997
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_EU_SWERC/1997/index.html)
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
using namespace std;

const int nr_coefficients_max = 10;
enum tree_node_types {program, op, loop_nr, loop};

struct tree_node {
	tree_node* parent_;
	tree_node* child_or_sibling_;
	int type_;
	int value_; // for op or loop_nr
	int coefficients_[nr_coefficients_max + 1];

	tree_node(tree_node* parent) : parent_(parent), child_or_sibling_(NULL), type_(program)
	{
		memset(coefficients_, 0, sizeof(coefficients_));
	}

	~tree_node()
	{
		delete child_or_sibling_;
	}

	tree_node* insert_node(int type, int value) {
		tree_node* tn = new tree_node(this);
		if (!child_or_sibling_) // first child
			child_or_sibling_ = tn;
		else {
			tree_node* stn = child_or_sibling_;
			while (stn->child_or_sibling_)
				stn = stn->child_or_sibling_;
			stn->child_or_sibling_ = tn;
		}
		tn->type_ = type; tn->value_ = value;
		if (tn->type_ == op)
			tn->coefficients_[0] = value;
		return tn;
	}

	void calculate_complexity() {
		for (tree_node* tn = child_or_sibling_; tn; tn = tn->child_or_sibling_)
			for (int i = 0; i <= nr_coefficients_max; i++)
				coefficients_[i] += tn->coefficients_[i];
		if (type_ == loop_nr)
			for (int i = 0; i <= nr_coefficients_max; i++)
				coefficients_[i] *= value_;
		else if (type_ == loop) {
			for (int i = nr_coefficients_max; i; i--)
				coefficients_[i] = coefficients_[i - 1];
			coefficients_[0] = 0;
		}
		delete child_or_sibling_;
		child_or_sibling_ = NULL;
	}

	void print_complexity() {
		bool printed = false;
		for (int i = nr_coefficients_max; i >= 0; i--)
			if (coefficients_[i]) {
				if (coefficients_[i] < 0)
					cout << '-';
				else if (printed)
					cout << '+';
				if (i) {
					if (abs(coefficients_[i]) > 1)
						cout << abs(coefficients_[i]) << '*';
					cout << 'n';
					if (i > 1)
						cout << '^' << i;
				}
				else
					cout << abs(coefficients_[i]);
				printed = true;
			}
		if (!printed)
			cout << 0;
	}
};

int main()
{
	int k;
	cin >> k;
	for (int program_nr = 1; program_nr <= k; program_nr++) {
		string s;
		cin >> s; // "BEGIN"
		tree_node* parent = new tree_node(NULL);
		while (true) {
			cin >> s;
			if (s == "LOOP") {
				cin >> s;
				parent = (s == "n") ?
					parent->insert_node(loop, -1) : parent->insert_node(loop_nr, atoi(s.c_str()));
			}
			else if (s == "OP") {
				cin >> s;
				parent->insert_node(op, atoi(s.c_str()));
			}
			else { // "END"
				parent->calculate_complexity();
				if (!parent->parent_)
					break;
#ifdef DEBUG
				parent->print_complexity();
				cout << endl;
#endif
				parent = parent->parent_;
			}
		}
		cout << "Program #" << program_nr << "\nRuntime = ";
		parent->print_complexity();
		cout << "\n\n";
		delete parent;
	}
	return 0;
}

