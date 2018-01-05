
/*
	UVa 10701 - Pre, in and post

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10701_Pre_in_and_post.cpp

	This problem is similar to UVa 536 - Tree Recovery.
*/

#include <cstdio>

/*
Construct Tree from given Inorder and Preorder traversals
	(http://www.geeksforgeeks.org/archives/6633)

Construct a tree from given inorder traversal and pre - order traversal
	(http://anandtechblog.blogspot.jp/2011/06/construct-tree-from-given-inorder.html)

	1. From the pre-order traversal, pick the first element which is root. (Root, left, right).
	2. Find that element in in-order sequence, Index at which element is found is the root index.
	3. As per In-order definition (Left, root, right): from the start of the array till index -1 is 
		on the left subtree and index + 1 to the end of the inorder array is right subtree. 
	Run the above steps from 1 to 3 on left subtree and right subtree recursively to form a tree.
*/

struct Tree
{
	char letter_;
	Tree* left_;
	Tree* right_;
	Tree(int letter) : letter_(letter), left_(NULL), right_(NULL) {}
	~Tree() {delete left_; delete right_;}
};

int search_element(char inorder[], int start, int end, char letter)
{
	for (int i = start; i <= end; i++)
		if (inorder[i] == letter)
			return i;
	return -1;
}

Tree* build_tree(char inorder[], char preorder[], int inorder_start, int inorder_end, int& preorder_index)
{
	if (inorder_start > inorder_end)
		return NULL;
	Tree* tree = new Tree(preorder[preorder_index++]);
	if (inorder_start == inorder_end)
		return tree;
	int inorder_index = search_element(inorder, inorder_start, inorder_end, tree->letter_);
	tree->left_ = build_tree(inorder, preorder, inorder_start, inorder_index - 1, preorder_index);
	tree->right_ = build_tree(inorder, preorder, inorder_index + 1, inorder_end, preorder_index);
	return tree;
}

void print_postorder(Tree* tree)
{
	if (tree) {
		print_postorder(tree->left_);
		print_postorder(tree->right_);
		putchar(tree->letter_);
	}
}

int main()
{
	int c;
	scanf("%d", &c);
	while (c--) {
		int length;
		const int nr_letters = 26;
		char inorder[nr_letters * 2 + 1], preorder[nr_letters * 2 + 1];
		scanf("%d %s %s", &length, preorder, inorder);
		int preorder_index = 0;
		Tree* root = build_tree(inorder, preorder, 0, length - 1, preorder_index);
		print_postorder(root);
		putchar('\n');
		delete root;
	}
	return 0;
}

