
/*
	UVa 11078 - Open Credit System

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_11078_Open_Credit_System.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int n_max = 100000, score_max = 150000;
int scores[n_max];
int min_scores[n_max]; // min_scores[i] is the minimum score between scores[i] and scores[n - 1]

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> scores[i];
		min_scores[n - 1] = scores[n - 1];
		for (int i = n - 2; i; i--)
			min_scores[i] = min(min_scores[i + 1], scores[i]);
		int max_score = -score_max * 2;
		for (int i = 0; i < n - 1; i++)
			max_score = max(max_score, scores[i] - min_scores[i + 1]);
		cout << max_score << endl;
	}
	return 0;
}

