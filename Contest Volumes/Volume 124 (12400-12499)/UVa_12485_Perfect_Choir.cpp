
/*
	UVa 12485 - Perfect Choir

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12485_Perfect_Choir.cpp

	This is an accepted solution.
*/

#include <cstdio>
using namespace std;

const int N_max = 10000;

int notes[N_max];

int main()
{
	int N;
	while (scanf("%d", &N) == 1) {
		int sum = 0;
		for (int i = 0; i < N; i++) {
			scanf("%d", &notes[i]);
			sum += notes[i];
		}
		int nr = -1;
		if (!(sum % N)) {
			nr = 1;
			sum /= N;
			for (int i = 0; notes[i] < sum; i++)
				nr += sum - notes[i];
		}
		printf("%d\n", nr);
	}
	return 0;
}

