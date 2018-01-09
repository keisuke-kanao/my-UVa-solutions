
/*
	UVa 839 - Not so Mobile

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_839_Not_so_Mobile.cpp
*/

#include <iostream>
using namespace std;

struct Tree
{
	int left_distance_, right_distance_;
	int left_weight_, right_weight_;
	Tree* left_;
	Tree* right_;
	Tree(int left_distance, int right_distance, int left_weight, int right_weight) :
		left_distance_(left_distance), right_distance_(right_distance),
		left_weight_(left_weight), right_weight_(right_weight), left_(NULL), right_(NULL) {}
	~Tree() {delete left_; delete right_;}
};

Tree* build_tree()
{
	int left_distance, right_distance, left_weight, right_weight;
	cin >> left_weight >> left_distance >> right_weight >> right_distance;
	Tree* t = new Tree(left_distance, right_distance, left_weight, right_weight);
	if (!left_weight)
		t->left_ = build_tree();
	if (!right_weight)
		t->right_ = build_tree();
	return t;
}

int calculate_tree_weight(Tree* t)
{
	if (t->left_ && (t->left_weight_ = calculate_tree_weight(t->left_)) == -1)
		return -1;
	if (t->right_ && (t->right_weight_ = calculate_tree_weight(t->right_)) == -1)
		return -1;
	return (t->left_weight_ * t->left_distance_ == t->right_weight_ * t->right_distance_) ?
		t->left_weight_ + t->right_weight_ : -1;
}

int main()
{
	int nr_cases;
	cin >> nr_cases;
	while (nr_cases--) {
		Tree* root = build_tree();
		cout << ((calculate_tree_weight(root) == -1) ? "NO\n" : "YES\n");
		delete root;
		if (nr_cases)
			cout << endl;
	}
	return 0;
}

