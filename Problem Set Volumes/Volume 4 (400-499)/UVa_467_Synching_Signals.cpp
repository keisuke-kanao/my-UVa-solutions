
/*
	UVa 467 - Synching Signals

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_467_Synching_Signals.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;

const int nr_signals_max = 10, nr_seconds_max = 3600;
int signals[nr_signals_max];
bool seconds[nr_seconds_max + 1];

int main()
{
	for (int ds = 1; ; ds++) {
		string line;
		if (!getline(cin, line))
			break;
		istringstream iss(line);
		int nr_signals = 0, s;
		while (iss >> s)
			signals[nr_signals++] = s;
		memset(seconds, 0, sizeof(seconds));
		for (int i = 0; i < nr_signals; i++) {
			int c = signals[i] * 2, g = signals[i] - 5;
			for (s = c; s <= nr_seconds_max; s += c)
				for (int j = s; j < s + g && j <= nr_seconds_max; j++)
					seconds[j] = true;
		}
		for (s = 0; s <= nr_seconds_max; s++)
			if (seconds[s]) {
				int i;
				for (i = 0; i < nr_signals; i++) {
					int j = s / signals[i];
					if (!(j & 1) && s >= signals[i] * j && s < signals[i] * (j + 1) - 5)
						;
					else
						break;
				}
				if (i == nr_signals)
					break;
			}
		if (s <= nr_seconds_max)
			cout << "Set " << ds << " synchs again at " << s / 60 << " minute(s) and " << s % 60 << " second(s) after all turning green.\n";
		else
			cout << "Set " << ds <<" is unable to synch after one hour.\n";
	}
	return 0;
}

