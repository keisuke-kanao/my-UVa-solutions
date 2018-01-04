
/*
	UVa 306 - Cipher

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_306_Cipher.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
using namespace std;

int main()
{
	const int n_max = 200;
	int numbers[n_max], cycles[n_max], indices[n_max];
		// cycles[i] is the number of sequence in which i-th character returns to its origianal position
	char s[n_max + 1], t[n_max + 1];
	while (true) {
		string line;
		istringstream iss;
		getline(cin, line);
		iss.str(line);
		int n;
		iss >> n;
		iss.clear();
		if (!n)
			break;
		getline(cin, line);
		iss.str(line);
		for (int i = 0; i < n; i++) {
			iss >> numbers[i];
			numbers[i]--;
		}
		iss.clear();
		for (int i = 0; i < n; i++) {
			cycles[i] = 0;
			if (i != numbers[i]) {
				cycles[i]++;
				for (int j = numbers[i]; j != i; j = numbers[j])
					cycles[i]++;
			}
#ifdef DEBUG
			if (i)
				cout << ' ';
			cout << cycles[i];
#endif
		}
#ifdef DEBUG
			cout << endl;
#endif
		while (true) {
			getline(cin, line);
			char *p;
			int k = strtol(line.c_str(), &p, 10);
			if (!k)
				break;
			strcpy(s, p + 1);
			int length = strlen(s);
			memset(s + length, ' ', n - length);
#ifdef DEBUG
			s[n] = '\0';
			cout << s << endl;
#endif
			for (int i = 0; i < n; i++)
				indices[i] = i;
			for (int i = 0; i < n; i++)
				if (cycles[i]) {
					for (int j = k % cycles[i]; j; j--)
						indices[i] = numbers[indices[i]];
				}
			for (int i = 0; i < n; i++)
				t[indices[i]] = s[i];
			t[n] = '\0';
			cout << t << endl;
		}
		cout << endl;
	}
	return 0;
}

