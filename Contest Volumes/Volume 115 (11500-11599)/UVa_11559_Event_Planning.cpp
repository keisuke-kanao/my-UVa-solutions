
/*
	UVa 11559 - Event Planning

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_11559_Event_Planning.cpp

	from Nordic Collegiate Programming Contest 2008
		(http://ncpc.idi.ntnu.no/ncpc2008/)
*/

#include <iostream>
using namespace std;

int main()
{
	int N, B, H, W;
	while (cin >> N >> B >> H >> W) {
		int min_cost = -1;
		for (int i = 0; i < H; i++) {
			int p;
			cin >> p;
			for (int j = 0; j < W; j++) {
				int a;
				cin >> a;
				if (a >= N) {
					int cost = N * p;
					if (cost <= B) {
						if (min_cost == -1 || min_cost > cost)
							min_cost = cost;
					}
				}
			}
		}
		if (min_cost != -1)
			cout << min_cost << endl;
		else
			cout << "stay home\n";
	}
	return 0;
}

