
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(int argc, char** argv)
{
	int nr_cases = 256;
	if (argc > 1)
		nr_cases = atoi(*++argv);
	srand(time(NULL));
	while (nr_cases--) {
		int n = rand() % 5 + 5;
		cout << n << endl;
		int m = rand() % (n * n) + 1;
		cout << m << endl;
		for (int i = 0; i < m; i++) {
			char c = (rand() % 2) ? 'H' : 'V';
			cout << c;
			int j, k;
			do {
				j = rand() % n + 1;
				k = rand() % n + 1;
			} while (c == 'H' && j == n || c == 'V' && k == n);
			cout << ' ' << j << ' ' << k << endl;
		}
	}
	return 0;
}

