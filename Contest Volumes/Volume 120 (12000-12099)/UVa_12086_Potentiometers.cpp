
/*
	UVa 12086 - Potentiometers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12086_Potentiometers.cpp

	An accepted solution.
*/

#include <cstdio>

const int N_max = 200000, ST_max = 524288;
int potmeters[N_max], segment_tree[ST_max];

inline int get_mid(int s, int e) {return s + (e - s) / 2;}

int construct_segment_tree(int* st, const int* array, int ss, int se, int si /* current node */)
{
	if (ss == se) // If there is one element in array, store it in current node of segment tree.
		st[si] = array[ss];
	else {
		// If there are more than one elements, then recurse for left and right subtrees and 
		// store the sum of values in this node.
		int mid = get_mid(ss, se);
		st[si] =  construct_segment_tree(st, array, ss, mid, si * 2 + 1) + construct_segment_tree(st, array, mid + 1, se, si * 2 + 2);
	}
    return st[si];
}

void update_segment_tree(int* st, int ss, int se, int i, int diff, int si /* current node */)
{
	if (i < ss || i > se) // If the element lies outside the range of this segment
		return;
	// If the element is in range of this node, then update the value of the node and its children.
	st[si] += diff;
	if (se != ss) {
		int mid = get_mid(ss, se);
		update_segment_tree(st, ss, mid, i, diff, 2 * si + 1);
		update_segment_tree(st, mid + 1, se, i, diff, 2 * si + 2);
    }
}

int get_sum(int* st, int ss, int se, int qs, int qe, int si)
{
	// If segment of this node is a part of given range, then return the sum of the segment.
	if (qs <= ss && qe >= se)
		return st[si];
	// If segment of this node is outside the given range
	if (se < qs || ss > qe)
		return 0;
	// If a part of this segment overlaps with the given range
	int mid = get_mid(ss, se);
	return get_sum(st, ss, mid, qs, qe, 2 * si + 1) + get_sum(st, mid + 1, se, qs, qe, 2 * si + 2);
}

int main()
{
	for (int cn = 1; ; cn++) {
		int N;
		scanf("%d", &N);
		if (!N)
			break;
		if (cn > 1)
			putchar('\n');
		for (int i = 0; i < N; i++)
			scanf("%d", &potmeters[i]);
		construct_segment_tree(segment_tree, potmeters, 0, N - 1, 0);
			// actual segment tree size is 2 * 2^(ceil(log2(N))) - 1
		printf("Case %d:\n", cn);
		while (true) {
			int diff, x, y, r;
			char s[8];
			scanf("%s", s);
			if (s[0] == 'E') // "END"
				break;
			else if (s[0] == 'S') {
				scanf("%d %d", &x, &r);
				int diff = r - potmeters[x - 1];
				potmeters[x - 1] = r;
				update_segment_tree(segment_tree, 0, N - 1, x - 1, diff, 0);
			}
			else {
				scanf("%d %d", &x, &y);
				printf("%d\n", get_sum(segment_tree, 0, N - 1, x - 1, y - 1, 0));;
			}
		}
	}
	return 0;
}

