
/*
	UVa 12582 - Wedding of Sultan

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12582_Wedding_of_Sultan.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

int main()
{
	const int nr_letters = 26;
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		string s;
		cin >> s;
		vector<int> letters(nr_letters, 0);
		stack<char> st;
		const char* p = s.c_str();
		st.push(*p++);
		for ( ; *p; p++) {
			if (st.top() != *p) {
				letters[st.top() - 'A']++;
				letters[*p - 'A']++;
				st.push(*p);
			}
			else
				st.pop();
		}
		cout << "Case " << t << endl;
		for (int i = 0; i < nr_letters; i++)
			if (letters[i])
				cout << static_cast<char>('A' + i) << " = " << letters[i] << endl;
	}
	return 0;
}

