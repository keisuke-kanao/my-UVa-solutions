
/*
	UVa 1196 - Tiling Up Blocks

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1196_Tiling_Up_Blocks.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int n_max = 10000;

struct block {
	int l_, m_;

	bool operator<(const block& b) const {return (l_ != b.l_) ? l_ < b.l_ : m_ < b.m_;}
} blocks[n_max];

int tail_indices[n_max], prev_indices[n_max];

int ceil_index(int l, int h, int ii)
{
	int i = blocks[ii].m_;
	while (h - l > 1) {
		int m = l + (h - l) / 2;
		if (blocks[tail_indices[m]].m_ > i)
			h = m;
		else
			l = m;
	}
	return h;
}

int lis(int n)
{
	int tail_length = 0;
	tail_indices[tail_length++] = 0;
	for (int i = 1; i < n; i++) {
		if (blocks[i].m_ < blocks[tail_indices[0]].m_) // a new smallest value
			tail_indices[0] = i;
		else if (blocks[i].m_ >= blocks[tail_indices[tail_length - 1]].m_) { // extend the largest sequence
			prev_indices[i] = tail_indices[tail_length - 1];
			tail_indices[tail_length++] = i;
		}
		else {
			int ci = ceil_index(-1, tail_length - 1, i);
			if (ci)
				prev_indices[i] = tail_indices[ci - 1];
			tail_indices[ci] = i;
		}
	}
	return tail_length;
}

int main()
{
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &blocks[i].l_, &blocks[i].m_);
			prev_indices[i] = -1;
		}
		sort(blocks, blocks + n);
		printf("%d\n", lis(n));
	}
	puts("*");
	return 0;
}

