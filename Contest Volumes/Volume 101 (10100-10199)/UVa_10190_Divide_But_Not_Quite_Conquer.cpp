
/*
	UVa 10190 - Divide, But Not Quite Conquer!

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10190_Divide_But_Not_Quite_Conquer.cpp
*/

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int n, m;
	while (cin >> n >> m) {
		bool boring = true;
		vector<int> sequence;
		if (n > 1 && m > 1) {
			while (true) {
				sequence.push_back(n);
				if (n == 1) {
					boring = false;
					break;
				}
				if (n % m)
					break;
				n /= m;
			}
		}
		if (boring)
			cout << "Boring!\n";
		else
			for (size_t i = 0, e = sequence.size(); i < e; i++)
				cout << sequence[i] << ((i == e - 1) ? '\n' : ' ');
	}
	return 0;
}

