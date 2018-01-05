
/*
	UVa 10961 - Chasing After Don Giovanni

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10961_Chasing_After_Don_Giovanni.cpp
*/

#include <cstdio>

const int ns_max = 100;

struct stop {
	int s_, a_;

	stop() {}
	stop(int s, int a) : s_(s), a_(a) {}
	stop(const stop& s) : s_(s.s_), a_(s.a_) {}
	bool operator==(const stop& s) const {return s_ == s.s_ && a_ == s.a_;}
	bool operator!=(const stop& s) const {return s_ != s.s_ || a_ != s.a_;}

} gs[ns_max + 1], ls[ns_max + 1];

bool move(stop& current, const stop& next)
{
	if (current != next) {
		if (current.s_ != next.s_) {
			if (current.s_ < next.s_)
				current.s_++;
			else
				current.s_--;
		}
		else {
			if (current.a_ < next.a_)
				current.a_++;
			else
				current.a_--;
		}
	}
	return current == next;
}

int main()
{
	int nc;
	scanf("%d", &nc);
	while (nc--) {
		scanf("%d %d", &gs[0].s_, &gs[0].a_);
		scanf("%d %d", &ls[0].s_, &ls[0].a_);
		int gn, ln;
		scanf("%d", &ln);
		ln++;
		for (int i = 1; i < ln; i++)
			scanf("%d %d", &ls[i].s_, &ls[i].a_);
		scanf("%d", &gn);
		gn++;
		for (int i = 1; i < gn; i++)
			scanf("%d %d", &gs[i].s_, &gs[i].a_);
		int li = 0, gi = 0;
		stop l(ls[0]), g(gs[0]);
		while (li < ln - 1 && gi < gn - 1) {
			if (l == g)
				break;
			if (move(l, ls[li + 1]))
				li++;
			if (move(g, gs[gi + 1]))
				gi++;
#ifdef DEBUG
			printf("l: [%d, %d], g: [%d, %d]\n", l.s_, l.a_, g.s_, g.a_);
#endif
		}
		puts((l == g && li != ln - 1) ? "No" : "Yes");
		if (nc)
			putchar('\n');
	}
	return 0;
}

