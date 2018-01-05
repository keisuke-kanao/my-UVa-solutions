
/*
	UVa 10929 - You can say 11

	To build using Visual Studio 2008:
		cl -EHsc -O2 you_can_say_11.cpp
*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
	while (true) {
		string n;
		cin >> n;
		bool end_of_input = true;
		int s = 0;
		for (int i = 0, j = n.length() - 1; j >= 0; i++, j--) {
			int k = n[j] - '0';
			if (k)
				end_of_input = false;
			if (i & 1)
				s -= k;
			else
				s += k;
		}
		if (end_of_input)
			break;
		cout << n << ((s % 11) ? " is not a multiple of 11.\n" : " is a multiple of 11.\n");
	}
	return 0;
}

