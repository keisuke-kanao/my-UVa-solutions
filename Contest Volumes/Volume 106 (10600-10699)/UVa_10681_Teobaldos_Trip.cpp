
/*
	UVa 10681 - Teobaldo's Trip

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10681_Teobaldos_Trip.cpp
*/

#include <iostream>
using namespace std;

const int c_max = 100, d_max = 200;

bool links[c_max + 1][c_max + 1];
bool travel[d_max + 1][c_max + 1]; // travel[k][i] is true if Teobaldo can travel to i in k days

int main()
{
	while (true) {
		int c, l;
		cin >> c >> l;
		if (!c && !l)
			break;
		for (int i = 1; i <= c; i++)
			for (int j = 1; j <= c; j++)
				links[i][j] = false;
		while (l--) {
			int a, b;
			cin >> a >> b;
			links[a][b] = links[b][a] = true;
		}
		int s, e, d;
		cin >> s >> e >> d;
		for (int k = 0; k <= d; k++)
			for (int i = 1; i <= c; i++)
				travel[k][i] = false;
		travel[0][s] = true;
		for (int k = 1; k <= d; k++)
			for (int i = 1; i <= c; i++)
				for (int j = 1; j <= c; j++)
					if (travel[k - 1][j] && links[j][i])
						travel[k][i] = true;
		cout << ((travel[d][e]) ? "Yes, Teobaldo can travel.\n" : "No, Teobaldo can not travel.\n");
	}
	return 0;
}

