
/*
	UVa 548 - Tree

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_548_Tree.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <limits>
using namespace std;

/*
Given inorder and postorder traversals construct a binary tree
	(http://geeksforgeeks.org/forum/topic/given-inorder-and-postorder-traversals-construct-a-binary-tree)

Construct a given tree from inorder and post order traversal
	(http://anandtechblog.blogspot.com/2011/06/construct-given-tree-from-inorder-and.html)

	1. Start with last element of post order sequence which happens to be the root.
	2. Create a node of that element.
	3. Search that element in inorder sequence, get its index.
	4. First create the right sub tree with start index = index + 1, end index = end.
	5. Then create the left sub tree with start index = start,  end index = index - 1.
	6. Repeat the above steps recursively.
*/

struct Tree
{
	int value_;
	Tree* left_;
	Tree* right_;
	Tree(int value) : value_(value), left_(NULL), right_(NULL) {}
	~Tree() {delete left_; delete right_;}
};

int get_value_index(const vector<int>& values, int left, int right, int value)
{
	for (int i = left; i <= right; i++)
 		if(values[i] == value)
			return i;
	return -1;
}

Tree* build_tree(const vector<int>& in_order, const vector<int>& post_order, int left, int right, int pos)
{
	if(left > right)
		return NULL;
	Tree* t = new Tree(post_order[pos]);
	int index = get_value_index(in_order, left, right, t->value_);
	t->right_ = build_tree(in_order, post_order, index + 1, right, pos - 1);
	t->left_ = build_tree(in_order, post_order, left, index - 1, pos - 1 - (right - index));
	return t;
}

void calculate_tree_path(Tree* t, stack<int>& s, int& min_path, int& min_leaf)
{
	int path = t->value_;
	if (!s.empty())
		path += s.top();
	if (!t->left_ && !t->right_) {
		if (path < min_path) {
			min_path = path;
			min_leaf = t->value_;
		}
		else if (path == min_path && min_leaf > t->value_)
			min_leaf = t->value_;
	}
	else {
		s.push(path);
		if (t->left_)
			calculate_tree_path(t->left_, s, min_path, min_leaf);
		if (t->right_)
			calculate_tree_path(t->right_, s, min_path, min_leaf);
		s.pop();
	}
}

int main()
{
	string line;
	while (getline(cin, line)) {
		istringstream iss(line);
		int value;
		vector<int> in_order;
		while (iss >> value)
			in_order.push_back(value);
		iss.clear();
		int nr_values = in_order.size();
		getline(cin, line);
		iss.str(line);
		vector<int> post_order(nr_values);
		for (int i = 0; i < nr_values; i++)
			iss >> post_order[i];
		Tree* root = build_tree(in_order, post_order, 0, nr_values - 1, nr_values - 1);
		stack<int> s;
		int min_path = numeric_limits<int>::max(), min_leaf;
		calculate_tree_path(root, s, min_path, min_leaf);
		cout << min_leaf << endl;
		delete root;
	}
	return 0;
}

