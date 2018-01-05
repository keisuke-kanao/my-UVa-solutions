
/*
	UVa 11292 - Dragon of Loowater

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11292_Dragon_of_Loowater.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int n_max = 20000, m_max = 20000;
int heads[n_max], heights[m_max];

int main()
{
	while (true) {
		int n, m;
		cin >> n >> m;
		if (!n && !m)
			break;
		for (int i = 0; i < n; i++)
			cin >> heads[i];
		for (int i = 0; i < m; i++)
			cin >> heights[i];
		int coins = 0;
		if (n > m)
			coins = -1;
		else {
			sort(heads, heads + n);
			sort(heights, heights + m);
			for (int i = 0, j = 0; i < n; i++) {
				for ( ; j < m; j++)
					if (heights[j] >= heads[i])
						break;
				if (j == m) {
					coins = -1; break;
				}
				else
					coins += heights[j++];
			}
		}
		if (coins == -1)
			cout << "Loowater is doomed!\n";
		else
			cout << coins << endl;
	}
	return 0;
}

