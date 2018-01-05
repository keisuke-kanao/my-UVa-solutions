
/*
	UVa 10354 - Avoiding Your Boss

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10354_Avoiding_Your_Boss.cpp
*/

#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

const int P_max = 100;
bool vertices[P_max + 1];
int boss_matrix[P_max + 1][P_max + 1], your_matrix[P_max + 1][P_max + 1];

int main()
{
	int P, R, BH, OF, YH, M;
	while (cin >> P >> R >> BH >> OF >> YH >> M) {
		for (int i = 1; i <= P; i++) {
			vertices[i] = true;
			for (int j = 1; j <= P; j++)
				boss_matrix[i][j] = your_matrix[i][j] = (i == j) ? 0 : numeric_limits<int>::max();
		}
		while (R--) {
			int p1, p2, d;
			cin >> p1 >> p2 >> d;
			boss_matrix[p1][p2] = boss_matrix[p2][p1] = your_matrix[p1][p2] = your_matrix[p2][p1] = d;
		}
		for (int k = 1; k <= P; k++)
			for (int i = 1; i <= P; i++)
				for (int j = 1; j <= P; j++)
					if (boss_matrix[i][k] != numeric_limits<int>::max() && boss_matrix[k][j] != numeric_limits<int>::max()) {
						int through_k = boss_matrix[i][k] + boss_matrix[k][j];
 						if (through_k < boss_matrix[i][j])
							boss_matrix[i][j] = through_k;
					}
		int d = boss_matrix[BH][OF];
		if (d != numeric_limits<int>::max()) {
			for (int k = 1; k <= P; k++)
				if (boss_matrix[BH][k] + boss_matrix[k][OF] == d)
					vertices[k] = false;
		}
		d = numeric_limits<int>::max();
		if (vertices[YH] && vertices[M]) {
			for (int k = 1; k <= P; k++) {
				if (!vertices[k])
					continue;
				for (int i = 1; i <= P; i++) {
					if (!vertices[i])
						continue;
					for (int j = 1; j <= P; j++) {
						if (!vertices[j])
							continue;
						if (your_matrix[i][k] != numeric_limits<int>::max() && your_matrix[k][j] != numeric_limits<int>::max()) {
							int through_k = your_matrix[i][k] + your_matrix[k][j];
 							if (through_k < your_matrix[i][j])
								your_matrix[i][j] = through_k;
						}
					}
				}
			}
			d = your_matrix[YH][M];
		}
		if (d != numeric_limits<int>::max())
			cout << d << endl;
		else
			cout << "MISSION IMPOSSIBLE.\n";
	}
	return 0;
}

