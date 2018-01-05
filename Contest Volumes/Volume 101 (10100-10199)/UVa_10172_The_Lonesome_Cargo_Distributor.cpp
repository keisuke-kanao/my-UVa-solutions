
/*
	UVa 10172 - The Lonesome Cargo Distributor

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10172_The_Lonesome_Cargo_Distributor.cpp
*/

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

int main()
{
	int SET;
	cin >> SET;
	while (SET--) {
		int N, S, Q;
		cin >> N >> S >> Q;
		vector< queue<int> > stations(N);
		for (int i = 0; i < N; i++) { // populate the stations with their initial cargoes
			int Qi;
			cin >> Qi;
			while (Qi--) {
				int cargo;
				cin >> cargo;
				stations[i].push(cargo - 1);
			}
		}
		int nr_minutes = 0;
		stack<int> carrier; 
		for (int i = 0; ; i = (i + 1) % N) {
			queue<int>& station = stations[i];
			while (!carrier.empty()) { // unload cargoes
				int cargo = carrier.top();
				if (cargo == i) {
					carrier.pop();
					nr_minutes++;
				}
				else if (station.size() < Q) {
					carrier.pop();
					nr_minutes++;
					station.push(cargo);
				}
				else
					break;
			}
			while (carrier.size() < S && !station.empty()) { // load cargoes
				carrier.push(station.front());
				station.pop();
				nr_minutes++;
			}
			bool done = carrier.empty();
			if (done) {
				for (int j = 0; j < N; j++)
					if (!stations[j].empty()) {
						done = false; break;
					}
			}
			if (done)
				break;
			nr_minutes += 2;
		}
		cout << nr_minutes << endl;
	}
	return 0;
}

