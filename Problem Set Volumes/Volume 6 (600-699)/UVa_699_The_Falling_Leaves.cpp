
/*
	UVa 699 - The Falling Leaves

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_699_The_Falling_Leaves.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Tree
{
	int nr_leaves_;
	int pos_;
	Tree* left_;
	Tree* right_;
	Tree(int nr_leaves, int pos) : nr_leaves_(nr_leaves), pos_(pos), left_(NULL), right_(NULL) {}
	~Tree() {delete left_; delete right_;}
};

void build_tree(Tree* t, int& min_pos, int& max_pos)
{
	min_pos = min(min_pos, t->pos_);
	max_pos = max(max_pos, t->pos_);
	int nr_leaves;
	cin >> nr_leaves;
	if (nr_leaves != -1) {
		t->left_ = new Tree(nr_leaves, t->pos_ - 1);
		build_tree(t->left_, min_pos, max_pos);
	}
	cin >> nr_leaves;
	if (nr_leaves != -1) {
		t->right_ = new Tree(nr_leaves, t->pos_ + 1);
		build_tree(t->right_, min_pos, max_pos);
	}
}

void collect_leaves(Tree* t, int pos, vector<int>& piles)
{
	piles[pos + t->pos_] += t->nr_leaves_;
	if (t->left_)
		collect_leaves(t->left_, pos, piles);
	if (t->right_)
		collect_leaves(t->right_, pos, piles);
}

int main()
{
	for (int c = 1; ; c++) {
		int min_pos = 0, max_pos = 0;
		int nr_leaves;
		cin >> nr_leaves;
		if (nr_leaves == -1)
			break;
		Tree* root = new Tree(nr_leaves, 0);
		build_tree(root, min_pos, max_pos);
		vector<int> piles(max_pos - min_pos + 1, 0);
		collect_leaves(root, -min_pos, piles);
		delete root;
		cout << "Case " << c << ":\n";
		for (size_t i = 0, e = piles.size(); i < e; i++)
			cout << piles[i] << ((i == e - 1) ? '\n' : ' ');
		cout << endl;
	}
	return 0;
}

