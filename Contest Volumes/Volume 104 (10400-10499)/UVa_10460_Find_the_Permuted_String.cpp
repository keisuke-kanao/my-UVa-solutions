
/*
	UVa 10460 - Find the Permuted String

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10460_Find_the_Permuted_String.cpp
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--) {
		string s;
		cin >> s;
		int i;
		cin >> i;
		i--;
		int n = static_cast<int>(s.length());
		vector<int> indices(n);
		for (int j = n; j; j--) {
			indices[j - 1] = i % j;
			i /= j;
		}
		vector<char> ps;
		for (int j = 0; j < n; j++)
			ps.insert(ps.begin() + indices[j], s[j]);
		for (int i = 0; i < n; i++)
			cout << ps[i];
		cout << endl;
	}
	return 0;
}

