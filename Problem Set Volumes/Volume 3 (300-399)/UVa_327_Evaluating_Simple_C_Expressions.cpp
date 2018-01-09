
/*
	UVa 327 - Evaluating Simple C Expressions

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_327_Evaluating_Simple_C_Expressions.cpp

	from ACM 1993 North Central problem set Problem D
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_NorthCen/1993/index.html)
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <cctype>
using namespace std;

struct Tree
{
	char variable_or_binary_; // 'a' - 'z' or '+' / '-'
	enum {unary_none, unary_pre_inc, unary_post_inc, unary_pre_dec, unary_post_dec};
	int unary_; 
	Tree* left_;
	Tree* right_;
	Tree(int v_or_b) : variable_or_binary_(v_or_b), unary_(unary_none), left_(NULL), right_(NULL) {}
	Tree(int v_or_b, int unary) : variable_or_binary_(v_or_b), unary_(unary), left_(NULL), right_(NULL) {}
	~Tree() {delete left_; delete right_;}
};

char* remove_spaces(const char* p)
{
	char* q = new char[strlen(p) + 1];
	char* r = q;
	for ( ; *p; p++)
		if (!isspace(*p))
			*r++ = *p;
	*r = '\0';
	return q;
}

Tree* add_to_tree(Tree* root, Tree* t)
{
	if (t->variable_or_binary_ == '+' || t->variable_or_binary_ == '-') {
		t->left_ = root; root = t;
	}
	else if (root)
		root->right_ = t;
	else
		root = t;
	return root;
}

int evaluate_tree(Tree* t, bool used_variables[], int variable_values[])
{
	if (t->variable_or_binary_ == '+' || t->variable_or_binary_ == '-') {
		int left_value = evaluate_tree(t->left_, used_variables, variable_values);
		int right_value = evaluate_tree(t->right_, used_variables, variable_values);
		return (t->variable_or_binary_ == '+') ? left_value + right_value : left_value - right_value;
	}
	else {
		int i = t->variable_or_binary_ - 'a';
		used_variables[i] = true;
		if (t->unary_ == Tree::unary_pre_inc)
			variable_values[i]++;
		else if (t->unary_ == Tree::unary_pre_dec)
			variable_values[i]--;
		int value = variable_values[i];
		if (t->unary_ == Tree::unary_post_inc)
			variable_values[i]++;
		else if (t->unary_ == Tree::unary_post_dec)
			variable_values[i]--;
		return value;
	}
}

int main()
{
	const int nr_variables = 'z' - 'a' + 1;
	bool used_variables[nr_variables];
	int variable_values[nr_variables];
	string es;
	while (getline(cin, es)) {
		char* ps = remove_spaces(es.c_str());
		Tree* root = NULL;
		for (int i = 0, length = strlen(ps); i < length; i++) {
			if (ps[i] == '+') {
				if (i < length - 2 && ps[i + 1] == '+' && islower(ps[i + 2])) {
					root = add_to_tree(root, new Tree(ps[i + 2], Tree::unary_pre_inc));
					i += 2;
				}
				else
					root = add_to_tree(root, new Tree(ps[i])); // binary '+'
			}
			else if (ps[i] == '-') {
				if (i < length - 2 && ps[i + 1] == '-' && islower(ps[i + 2])) {
					root = add_to_tree(root, new Tree(ps[i + 2], Tree::unary_pre_dec));
					i += 2;
				}
				else
					root = add_to_tree(root, new Tree(ps[i])); // binary '-'
			}
			else {
				if (i < length - 2 && ps[i + 1] == '+' && ps[i + 2] == '+') {
					root = add_to_tree(root, new Tree(ps[i], Tree::unary_post_inc));
					i += 2;
				}
				else if (i < length - 2 && ps[i + 1] == '-' && ps[i + 2] == '-') {
					root = add_to_tree(root, new Tree(ps[i], Tree::unary_post_dec));
					i += 2;
				}
				else
					root = add_to_tree(root, new Tree(ps[i])); // variable
			}
		}
		for (int i = 0; i < nr_variables; i++) {
			used_variables[i] = false;
			variable_values[i] = i + 1;
		}
		int value = evaluate_tree(root, used_variables, variable_values);
		cout << "Expression: " << es << endl;
		cout << "    value = " << value << endl;
		for (int i = 0; i < nr_variables; i++)
			if (used_variables[i]) {
				char c = 'a' + i;
				cout << "    " << c << " = " << variable_values[i] << endl;
			}
		delete[] ps;
		delete root;
	}
	return 0;
}


