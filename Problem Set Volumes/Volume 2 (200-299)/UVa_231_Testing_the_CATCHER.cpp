
/*
	UVa 231 - Testing the CATCHER

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_231_Testing_the_CATCHER.cpp
*/

/*
	This is a longest decreasing subsequence problem.
	The longest decreasing subsequence is equivalent in computational complexity, 
	by negation of all numbers, to the longest increasing subsequence.
*/

#include <iostream>
#include <vector>
using namespace std;

int lds(const vector<int>& heights)
{
	int n = heights.size();
	vector<int> l(n);
	int length = 1;
	l[0] = 1;
	for (int i = 1; i < n; i++) {
		l[i] = 1;
		for (int j = 0; j < i; j++)
			if (heights[j] >= heights[i]) {
				if (l[i] < 1 + l[j]) {
					l[i] = 1 + l[j];
				}
			}
		if (length < l[i])
			length = l[i];
	}
	return length;
}

int main()
{
	for (int t = 1; ; t++) {
		int h;
		cin >> h;
		if (h == -1)
			break;
		if (t > 1)
			cout << endl;
		vector<int> heights;
		do {
			heights.push_back(h);
			cin >> h;
		} while (h != -1);
		int l = lds(heights);
		cout << "Test #" << t << ":\n";
		cout << "  maximum possible interceptions: " << l << endl;
	}
	return 0;
}

