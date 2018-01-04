
/*
	UVa 11988 - Broken Keyboard (a.k.a. Beiju Text)

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_11988_Broken_Keyboard.cpp
*/

#include <cstdio>

const int nr_chars_max = 100000;
char s[nr_chars_max];

struct cnode { // doubly-linked list node
	char c_;
	cnode *prev_, *next_;
};

cnode cnodes[nr_chars_max];

int main()
{
	while (gets(s)) {
		cnode head;
		head.prev_ = head.next_ = &head;
		char* p;
		cnode* pcnode = &head;
		int cni = 0;
		for (p = s; *p; p++) {
			if (*p == '[')
				pcnode = &head;
			else if (*p == ']')
				pcnode = head.prev_;
			else {
				cnode* pcn = &cnodes[cni++];
				pcn->c_ = *p;
				pcn->prev_ = pcnode; pcn->next_ = pcnode->next_;
				pcnode->next_->prev_ = pcn; pcnode->next_ = pcn;
				pcnode = pcn;
			}
		}
		p = s;
		for (pcnode = head.next_; pcnode != &head; pcnode = pcnode->next_)
			*p++ = pcnode->c_;
		*p = '\0';
		puts(s);
	}
	return 0;
}

