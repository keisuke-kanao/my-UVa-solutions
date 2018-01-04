
/*
	UVa 11987 - Almost Union-Find

	To build using Visucal Studio 2012:
		cl -EHsc UVa_11987_Almost_Union-Find.cpp
*/

#include <cstdio>

const int n_max = 100000 + 1;

class almost_union_find {
public:
	void make_set(int i);
	int find_set(int i) const;
	void move(int i, int j);
	void do_union(int i, int j);
	int size(int i) const;
	long long sum(int i) const;

private:
	struct set {
		int size_;
		int head_, tail_;
	};

	struct element {
		int set_;
		int prev_, next_;
	};

	int n_;
	set sets_[n_max];
	element elements_[n_max];
};

void almost_union_find::make_set(int i)
{
	sets_[i].size_ = 1;
	sets_[i].head_ = sets_[i].tail_ = i;
	elements_[i].set_ = i;
	elements_[i].prev_ = elements_[i].next_ = -1;
}

int almost_union_find::find_set(int i) const
{
	return sets_[elements_[i].set_].head_;
}

void almost_union_find::do_union(int i, int j)
{
	if (elements_[i].set_ == elements_[j].set_)
		return;
	set &si = sets_[elements_[i].set_], &sj = sets_[elements_[j].set_];
	if (si.size_ >= sj.size_) {
		si.size_ += sj.size_;
		elements_[sj.head_].prev_ = si.tail_;
		elements_[si.tail_].next_ = sj.head_;
		si.tail_ = sj.tail_;
		for (int next = sj.head_; next != -1; next = elements_[next].next_)
			elements_[next].set_ = elements_[i].set_;
	}
	else {
		sj.size_ += si.size_;
		elements_[si.head_].prev_ = sj.tail_;
		elements_[sj.tail_].next_ = si.head_;
		sj.tail_ = si.tail_;
		for (int next = si.head_; next != -1; next = elements_[next].next_)
			elements_[next].set_ = elements_[j].set_;
	}
}

void almost_union_find::move(int i, int j)
{
	if (elements_[i].set_ == elements_[j].set_)
		return;
	int prev, next;
	set &si = sets_[elements_[i].set_], &sj = sets_[elements_[j].set_];
	if (si.size_ > 1) {
		si.size_--;
		if (si.head_ == i) {
			next = elements_[i].next_;
			si.head_ = next;
			elements_[next].prev_ = -1;
		}
		else if (si.tail_ == i) {
			prev = elements_[i].prev_;
			si.tail_ = prev;
			elements_[prev].next_ = -1;
		}
		else {
			prev = elements_[i].prev_, next = elements_[i].next_;
			elements_[prev].next_ = next, elements_[next].prev_ = prev;
		}
	}
	sj.size_++;
	elements_[i].set_ = elements_[j].set_;
	elements_[sj.tail_].next_ = i;
	elements_[i].prev_ = sj.tail_, elements_[i].next_ = -1;
	sj.tail_ = i;
}

int almost_union_find::size(int i) const
{
	return sets_[elements_[i].set_].size_;
}

long long almost_union_find::sum(int i) const
{
	long long s = 0;
	for (int next = sets_[elements_[i].set_].head_; next != -1; next = elements_[next].next_)
		s += next;
	return s;
}

almost_union_find auf;

int main()
{
	int n, m;
	while (scanf("%d %d", &n, &m) != EOF) {
		for (int i = 1; i <= n; i++)
			auf.make_set(i);
		while (m--) {
			int c, p, q;
			scanf("%d", &c);
			switch (c) {
			case 1:
				scanf("%d %d", &p, &q);
				auf.do_union(p, q);
				break;
			case 2:
				scanf("%d %d", &p, &q);
				auf.move(p, q);
				break;
			case 3:
				scanf("%d", &p);
				printf("%d %lld\n", auf.size(p), auf.sum(p));
				break;
			}
		}
	}
	return 0;
}

