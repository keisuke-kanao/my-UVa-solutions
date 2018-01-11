
/*
	UVa 437 - The Tower of Babylon

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_437_The_Tower_of_Babylon.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct block {
	int x_, y_, z_;
};

/*
	For each input line representing the values of x, y, and z, store six block instances, namely:
		{x, y, z}, {x, z, y}, {y, x, z}, {y, z, x}, {z, x, y}, {z, y, x}.
	Sort the vector of blocks in ascending order of x and y, and in descending order of z.
	Calculate the LIS (Longest Increasing SubSequence) for the vector of blocks.
*/

bool compare_block(const block& i, const block& j)
{
	if (i.x_ < j.x_)
		return true;
	else if (i.x_ > j.x_)
		return false;
	else if (i.y_ < j.y_)
		return true;
	else if (i.y_ > j.y_)
		return false;
	else
		return i.z_ > j.z_;
}

int lis(int n, const vector<block>& blocks)
{
	vector<int> l(n), prev(n);
	int length = blocks[0].z_;
	l[0] = blocks[0].z_;
	prev[0] = -1;
	for (int i = 1; i < n; i++) {
		l[i] = blocks[i].z_;
		prev[i] = -1;
		for (int j = 0; j < i; j++)
			if (blocks[j].x_ < blocks[i].x_ && blocks[j].y_ < blocks[i].y_) {
				if (l[i] < blocks[i].z_ + l[j]) {
					l[i] = blocks[i].z_ + l[j];
					prev[i] = j;
				}
			}
		if (length < l[i])
			length = l[i];
	}
	return length;
}

int main()
{
	for (int c = 1; ; c++) {
		int n;
		cin >> n;
		if (!n)
			break;
		vector<block> blocks(n * 6);
		for (int i = 0; i < n; i++) {
			int x, y, z;
			cin >> x >> y >> z;
			blocks[6 * i].x_ = x; blocks[6 * i].y_ = y; blocks[6 * i].z_ = z;
			blocks[6 * i + 1].x_ = x; blocks[6 * i + 1].y_ = z; blocks[6 * i + 1].z_ = y;
			blocks[6 * i + 2].x_ = y; blocks[6 * i + 2].y_ = x; blocks[6 * i + 2].z_ = z;
			blocks[6 * i + 3].x_ = y; blocks[6 * i + 3].y_ = z; blocks[6 * i + 3].z_ = x;
			blocks[6 * i + 4].x_ = z; blocks[6 * i + 4].y_ = x; blocks[6 * i + 4].z_ = y;
			blocks[6 * i + 5].x_ = z; blocks[6 * i + 5].y_ = y; blocks[6 * i + 5].z_ = x;
		}
		n *= 6;
		sort(blocks.begin(), blocks.end(), compare_block);
		cout << "Case " << c << ": maximum height = " << lis(n, blocks) << endl;
	}
	return 0;
}

