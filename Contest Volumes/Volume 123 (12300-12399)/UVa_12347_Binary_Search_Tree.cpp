
/*
	UVa 12347 - Binary Search Tree

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12347_Binary_Search_Tree.cpp
*/

#include <iostream>
using namespace std;

struct tree_node {
	int value_;
	tree_node* left_;
	tree_node* right_;

	tree_node(int value) : value_(value), left_(NULL), right_(NULL) {}
	tree_node* insert(int value) {
		tree_node* ti = new tree_node(value);
		tree_node* tj = this;
		while (true) {
			if (value < tj->value_) {
				if (!tj->left_) {
					tj->left_ = ti;
					break;
				}
				tj = tj->left_;
			}
			else {
				if (!tj->right_) {
					tj->right_ = ti;
					break;
				}
				tj = tj->right_;
			}
		}
		return ti;
	}

	void print_post_order() const
	{
		if (left_)
			left_->print_post_order();
		if (right_)
			right_->print_post_order();
		cout << value_ << endl;
	}
};

int main()
{
	int value;
	if (cin >> value) {
		tree_node* root = new tree_node(value);
		while (cin >> value)
			root->insert(value);
		root->print_post_order();
	}
	return 0;
}

