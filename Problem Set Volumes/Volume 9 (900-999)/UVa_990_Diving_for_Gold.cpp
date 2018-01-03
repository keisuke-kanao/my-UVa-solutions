
/*
	UVa 990 - Diving for Gold

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_990_Diving_for_Gold.cpp
*/

#include <cstdio>

const int n_max = 30, t_max = 1000;

struct treasure {
	int d_; // depth
	int v_; // quantity of gold
} treasures[n_max + 1];

struct state {
	int i_; // index to treasures[] to be recovered
	int v_; // amount of gold
	int recovered_[n_max + 1]; // recovered_[i] is the index to treasures[] previouslly recovered
} states[t_max + 1];


void print_recovered_treasures(int i, int recovered[], int n)
{
	if (recovered[i] == -1)
		printf("%d\n", n);
	else {
		print_recovered_treasures(recovered[i], recovered, n + 1);
		printf("%d %d\n", treasures[i].d_, treasures[i].v_);
	}
}

int main()
{
	bool printed = false;
	int t, w;
	while (scanf("%d %d", &t, &w) != EOF) {
		if (printed)
			putchar('\n');
		else
			printed = true;
		w *= 3;
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d %d", &treasures[i].d_, &treasures[i].v_);
		for (int i = 0; i <= t; i++)
			states[i].i_ = states[i].v_ = states[i].recovered_[0] = -1;
		states[0].v_ = states[0].i_ = 0;
		int tt = 0; // total time in seconds
		for (int i = 1; i <= n; i++) {
			int wt = treasures[i].d_ * w;
			tt += wt;
			if (tt > t)
				tt = t;
			for (int j = tt; j >= wt; j--)
				if (states[j - wt].v_ != -1) {
					int v = states[j - wt].v_ + treasures[i].v_;
					if (v > states[j].v_) {
						for (int k = 1; k < i; k++)
							states[j].recovered_[k] = states[j - wt].recovered_[k];
						states[j].recovered_[i] = states[j - wt].i_;
						states[j].i_ = i; states[j].v_ = v;
					}
				}
		}
		int max_v = 0, max_i = 0;
		for (int i = 1; i <= tt; i++)
			if (states[i].v_ != -1 && states[i].v_ > max_v)
				max_v = states[max_i = i].v_;
		printf("%d\n", max_v);
		print_recovered_treasures(states[max_i].i_, states[max_i].recovered_, 0);
	}
	return 0;
}

