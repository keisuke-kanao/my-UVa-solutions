
/*
	UVa 161 - Traffic Lights

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_161_Traffic_Lights.cpp
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <functional>
using namespace std;

const int orange_time = 5, allowed_time_max = 5 * 60 * 60;
const int nr_cycle_times_max = 100;
int cycle_times[nr_cycle_times_max + 1];

int traffic_lights(int n, int ci, int start_time, int end_time)
{
	if (ci == n)
		return start_time;
	else {
		int result = -1;
		int ct = cycle_times[ci];
		int d = start_time / ct;
		if (d & 1)
			d++;
		for (int t = ct * d; t < end_time; t += ct * 2) {
			int st = max(t, start_time), et = min(t + ct - orange_time, end_time);
			if (st <= allowed_time_max && st < et &&
				(result = traffic_lights(n, ci + 1, st, et)) != -1)
				break;
		}
		return result;
	}
}

int main()
{
	while (true) {
		cin >> cycle_times[0] >> cycle_times[1] >> cycle_times[2];
		if (!cycle_times[0] && !cycle_times[1] && !cycle_times[2])
			break;
		int nr_cycle_times = 2;
		if (cycle_times[2]) {
			nr_cycle_times++;
			while (true) {
				cin >> cycle_times[nr_cycle_times];
				if (!cycle_times[nr_cycle_times])
					break;
				nr_cycle_times++;
			}
		}
		sort(cycle_times, cycle_times + nr_cycle_times);
		int st, ct = cycle_times[0], result = -1;
		for (st = ct * 2; st <= allowed_time_max; st += ct * 2)
			if ((result = traffic_lights(nr_cycle_times, 1, st, st + ct - orange_time)) != -1)
				break;
		if (result != -1) {
			int h = result / 3600;
			result -= h * 3600;
			int m = result / 60;
			result -= m * 60;
			cout << setfill('0') << setw(2) << h << ':' << setw(2) << m << ':' <<
				setw(2) << result << endl;
		}
		else
			cout << "Signals fail to synchronise in 5 hours\n";
	}
	return 0;
}

