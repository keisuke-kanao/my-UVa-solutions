
/*
	UVa 12657 - Boxes in a Line

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12657_Boxes_in_a_Line.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int n_max = 100000;

struct list {
	int value_;
	list *left_, *right_;
} lists[n_max + 1];

void remove(list* l)
{
	l->right_->left_ = l->left_, l->left_->right_ = l->right_;
}

void insert_left(list* ll, list* l)
{
	l->left_->right_ = ll, ll->left_ = l->left_;
	ll->right_ = l, l->left_ = ll;
}

void insert_right(list* rl, list* l)
{
	l->right_->left_ = rl, rl->right_ = l->right_;
	rl->left_ = l, l->right_ = rl;
}

void swap_(list* ll, list* rl)
{
	if (ll->left_ != rl && ll->right_ != rl) {
		ll->left_->right_ = rl, ll->right_->left_= rl;
		rl->left_->right_ = ll, rl->right_->left_ = ll;
		swap(ll->left_, rl->left_);
		swap(ll->right_, rl->right_);
	}
	else if (ll->right_ == rl) {
		ll->left_->right_ = rl, rl->right_->left_ = ll;
		ll->right_ = rl->right_, rl->left_ = ll->left_;
		ll->left_ = rl, rl->right_ = ll;
	}
	else {
		ll->right_->left_ = rl, rl->left_->right_ = ll;
		ll->left_ = rl->left_, rl->right_ = ll->right_;
		ll->right_ = rl, rl->left_ = ll;
	}
}

#ifdef DEBUG
void print_list(bool reverse)
{
	if (reverse)
		for (list* l = lists[0].left_; l != &lists[0]; l = l->left_)
			printf("%d ", l->value_);
	else
		for (list* l = lists[0].right_; l != &lists[0]; l = l->right_)
			printf("%d ", l->value_);
	putchar('\n');
}
#endif

int main()
{
	for (int cn = 1; ; cn++) {
		int n, m;
		if (scanf("%d %d", &n, &m) == EOF)
			break;
		lists[0].left_ = &lists[n], lists[0].right_ = &lists[1];
		for (int i = 1; i < n; i++)
			lists[i].value_ = i,
				lists[i].left_ = &lists[i - 1], lists[i].right_ = &lists[i + 1];
		lists[n].value_ = n,
			lists[n].left_ = &lists[n - 1], lists[n].right_ = &lists[0];
		bool reverse = false;
		while (m--) {
			int c, X, Y;
			scanf("%d", &c);
			if (c != 4)
				scanf("%d %d", &X, &Y);
			switch (c) {
			case 1:
				if (reverse) {
					if (lists[X].left_ != &lists[Y]) {
						remove(&lists[X]);
						insert_right(&lists[X], &lists[Y]);
					}
				}
				else {
					if (lists[X].right_ != &lists[Y]) {
						remove(&lists[X]);
						insert_left(&lists[X], &lists[Y]);
					}
				}
				break;
			case 2:
				if (reverse) {
					if (lists[X].right_ != &lists[Y]) {
						remove(&lists[X]);
						insert_left(&lists[X], &lists[Y]);
					}
				}
				else {
					if (lists[X].left_ != &lists[Y]) {
						remove(&lists[X]);
						insert_right(&lists[X], &lists[Y]);
					}
				}
				break;
			case 3:
				swap_(&lists[X], &lists[Y]);
				break;
			case 4:
				reverse = !reverse;
				break;
			}
#ifdef DEBUG
			print_list(reverse);
#endif
		}
		bool odd = true;
		unsigned int s = 0;
		if (reverse) {
			for (list* l = lists[0].left_; l != &lists[0]; l = l->left_) {
				if (odd)
					odd = false, s += l->value_;
				else
					odd = true;
			}
		}
		else {
			for (list* l = lists[0].right_; l != &lists[0]; l = l->right_) {
				if (odd)
					odd = false, s += l->value_;
				else
					odd = true;
			}
		}
		printf("Case %d: %u\n", cn, s);
	}
	return 0;
}

