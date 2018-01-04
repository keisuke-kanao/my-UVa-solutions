
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	srand(time(NULL));
	int T = 50;
	cout << T << endl;
	while (T--) {
		int N = rand() % 10 + 1, K = rand() % 5 + 1;
		cout << N << ' ' << K << endl;
		const char nucleotides[] = {'A', 'C', 'G', 'T'};
		for (int i = 0; i < N; i++)
			cout << nucleotides[rand() % 4];
		cout << endl;
	}
	return 0;
}

