
/*
	UVa 978 - Lemmings Battle!

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_978_Lemmings_Battle.cpp
*/

#include <iostream>
#include <list>
#include <algorithm>
#include <functional>
using namespace std;

int main()
{
	int N;
	cin >> N;
	while (N--) {
		int B, SG, SB;
		cin >> B >> SG >> SB;
		list<int> sg, sb;
		while (SG--) {
			int i;
			cin >> i;
			sg.push_back(i);
		}
		while (SB--) {
			int i;
			cin >> i;
			sb.push_back(i);
		}
		while (true) {
			sg.sort(greater<int>());
			sb.sort(greater<int>());
			if (sg.empty() || sb.empty())
				break;
			int b = min(B, min(static_cast<int>(sg.size()), static_cast<int>(sb.size())));
			while (b--) {
				int g = sg.front(), b = sb.front();
				sg.pop_front(); sb.pop_front();
				if (g > b)
					sg.push_back(g - b);
				else if (g < b)
					sb.push_back(b - g);
			}
		}
		if (sg.empty() && sb.empty())
			cout << "green and blue died\n";
		else if (sg.empty()) {
			cout << "blue wins\n";
			for (list<int>::const_iterator li = sb.begin(), le = sb.end(); li != le; ++li)
				cout << *li << endl;
		}
		else {
			cout << "green wins\n";
			for (list<int>::const_iterator li = sg.begin(), le = sg.end(); li != le; ++li)
				cout << *li << endl;
		}
		if (N)
			cout << endl;
	}
	return 0;
}

