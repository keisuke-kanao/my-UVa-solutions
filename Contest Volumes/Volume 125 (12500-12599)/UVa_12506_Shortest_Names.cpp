
/*
	UVa 12506 - Shortest Names

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12506_Shortest_Names.cpp
*/

#include <cstdio>
#include <cstring>

/*
Used trie.
During the construction of trie, counted the number of occurrences of each trie node.
Then, treversed the trie and summed up the number of occurrences of letters except for the nodes 
whose parent node has the occurrence counter value of 1.
*/

const int nr_letters = 'z' - 'a' + 1, nr_chars_max = 1000000;
char name[nr_chars_max + 1];

struct trie_node {
	static int ctrs_[nr_letters];

	int ctr_;
	trie_node* children_[nr_letters];

	trie_node() : ctr_(0) {
		memset(children_, 0, sizeof(children_));
	}
	~trie_node() {
		for (int i = 0; i < nr_letters; i++)
			delete children_[i];
	}
	void insert(const char* s);
	void count_prefix(int ci);
};

int trie_node::ctrs_[nr_letters];

void trie_node::insert(const char* s)
{
	trie_node* p = this;
	for (int i = 0, length = strlen(s); i < length; i++) {
		int j = s[i] - 'a';
		if (!p->children_[j])
			p->children_[j] = new trie_node();
		p = p->children_[j];
		p->ctr_++;
	}
}

void trie_node::count_prefix(int ci)
{
	ctrs_[ci] += ctr_;
	if (ctr_ > 1)
		for (int i = 0; i < nr_letters; i++)
			if (children_[i])
				children_[i]->count_prefix(i);
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		memset(trie_node::ctrs_, 0, sizeof(trie_node::ctrs_));
		trie_node* root = new trie_node();
		while (n--) {
			scanf("%s", name);
			root->insert(name);
		}
		for (int i = 0; i < nr_letters; i++)
			if (root->children_[i])
				root->children_[i]->count_prefix(i);
		int ctr = 0;
		for (int i = 0; i < nr_letters; i++)
			ctr += trie_node::ctrs_[i];
		printf("%d\n", ctr);
		delete root;
	}
	return 0;
}

