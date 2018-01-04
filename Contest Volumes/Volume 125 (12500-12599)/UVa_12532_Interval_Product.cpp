
/*
	UVa 12532 - Interval Product

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12532_Interval_Product.cpp
*/

#include <cstdio>

const int N_max = 100000, ST_max =  262144;
int values[N_max], segment_tree[ST_max];

void build_segment_tree(int at, int lo, int hi)
{
	if (lo == hi) {
		segment_tree[at] = values[lo];
		return;
	}
	int mid = (lo + hi) / 2;
	build_segment_tree(2 * at, lo, mid);
	build_segment_tree(2 * at + 1, mid + 1, hi);
	segment_tree[at] = segment_tree[2 * at] * segment_tree[2 * at + 1];
}

void update_segment_tree(int at, int index, int value, int lo, int hi)
{
	if (index < lo || index > hi)
		return;
	if (lo == hi) {
		segment_tree[at] = value;
		return;
	}
	int mid = (lo + hi) / 2;
	update_segment_tree(2 * at, index, value, lo, mid);
	update_segment_tree(2 * at + 1, index, value, mid + 1, hi);
	segment_tree[at] = segment_tree[2 * at] * segment_tree[2 * at + 1];
}

int query_product(int at, int lo, int hi, int qs, int qe)
{
	if (qs > hi || qe < lo)
		return 1;
	if (lo >= qs && hi <= qe)
		return segment_tree[at];
	int mid = (lo + hi) / 2;
	return query_product(2 * at, lo, mid, qs, qe) * query_product(2 * at + 1, mid + 1, hi, qs, qe);
}

int main()
{
	int N, K;
	while (scanf("%d %d", &N, &K) != EOF) {
		for (int i = 0; i < N; i++) {
			int x;
			scanf("%d", &x);
			values[i] = (x > 0) ? 1 : ((x < 0) ? -1 : 0);
		}
		build_segment_tree(1, 0, N - 1);
		while (K--) {
			int i, j;
			char s[2];
			scanf("%s %d %d", s, &i, &j);
			if (s[0] == 'C') {
				j = (j > 0) ? 1 : ((j < 0) ? -1 : 0);
                update_segment_tree(1, i - 1, j, 0, N - 1);
			}
			else {
				int p = query_product(1, 0, N - 1, i - 1, j - 1);
				putchar((p > 0) ? '+' : ((p < 0) ? '-' : '0'));
			}
		}
		putchar('\n');
	}
	return 0;
}

