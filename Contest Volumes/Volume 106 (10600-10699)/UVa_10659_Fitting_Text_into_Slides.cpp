
/*
	UVa 10659 - Fitting Text into Slides

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10659_Fitting_Text_into_Slides.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int P_min = 8, P_max = 28;

int fit(int M, int p_max, int X, int Y, const vector< vector<int> >& paragraphs)
{
	for (int p = p_max; p >= P_min; p--) {
		int y = 0;
		for (int i = 0; i < M; i++) {
			const vector<int>& paragraph = paragraphs[i];
			int x = 0;
			for (size_t j = 0, je = paragraph.size(); j < je; j++) {
				int k = paragraph[j] * p;
				if (k > X) {
					if (j < je - 1) { // exclude a space
						if (x + k - p <= X) {
							x = 0;
							y += p;
						}
						else if (k - p <= X) {
							if (x) {
								x = 0;
								y += p;
							}
							y += p;
						}
						else
							y = Y + 1;
						if (y > Y)
							break;
					}
					else {
						y = Y + 1;
						break;
					}
				}
				else if (x + k > X) {
					if (j < je - 1 && x + k - p <= X) { // exclude a space
						x = 0;
						y += p;
					}
					else {
						x = k;
						y += p;
					}
					if (y > Y)
						break;
				}
				else {
					x += k;
					if (x == X) {
						x = 0;
						y += p;
					}
				}
			}
			if (x)
				y += p;
			if (y > Y)
				break;
		}
		if (y <= Y)
			return p;
	}
	return -1;
}

int main()
{
	int N;
	cin >> N;
	while (N--) {
		int M;
		cin >> M;
		string s;
		getline(cin, s);
		int max_length = 0;
		vector< vector<int> > paragraphs(M);
		for (int i = 0; i < M; i++) {
			getline(cin, s);
			vector<int>& paragraph = paragraphs[i];
			for (const char *p = s.c_str(); *p; ) {
				const char* q = p;
				while (*p)
					if (*p++ == ' ')
						break;
				int length = p - q;
				paragraph.push_back(length);
				if (*p)
					length--; // exclude a space
				max_length = max(max_length, length);
			}
		}
		int X, Y;
		cin >> X >> Y;
		int p = -1, p_max = min(P_max, X / max_length);
		if (p_max >= P_min)
			p = fit(M, p_max, X, Y, paragraphs);
		if (p != -1)
			cout << p << endl;
		else
			cout << "No solution\n";
	}
	return 0;
}

