
/*
	UVa 11488 - Hyper Prefix Sets

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11488_Hyper_Prefix_Sets.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

/*
Used trie.
During the construction of trie, counted the number of occurrences of each trie node and 
also calculated the goodnes for the node.
*/

const int nr_letters = '1' - '0' + 1, nr_chars_max = 200;

struct trie_node {
	static int max_goodness;

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
	void calculate_goodness(int length);
};

int trie_node::max_goodness;

void trie_node::insert(const char* s)
{
	trie_node* p = this;
	for (int i = 0, length = strlen(s); i < length; i++) {
		int j = s[i] - '0';
		if (!p->children_[j])
			p->children_[j] = new trie_node();
		p = p->children_[j];
		p->ctr_++;
		max_goodness = max(max_goodness, (i + 1) * p->ctr_);
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		trie_node::max_goodness = 0;
		trie_node* root = new trie_node();
		while (n--) {
			char s[nr_chars_max + 1];
			scanf("%s", s);
			root->insert(s);
		}
		printf("%d\n", trie_node::max_goodness);
		delete root;
	}
	return 0;
}

