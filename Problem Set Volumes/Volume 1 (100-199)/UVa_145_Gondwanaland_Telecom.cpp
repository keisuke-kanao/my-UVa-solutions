
/*
	UVa 145 - Gondwanaland Telecom

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_145_Gondwanaland_Telecom.cpp
*/

#include <cstdio>

const int nr_steps = 5, nr_time_of_days = 3;

const double charging_rates[nr_steps][nr_time_of_days] = {
	{0.10, 0.06, 0.02},
	{0.25, 0.15, 0.05},
	{0.53, 0.33, 0.13},
	{0.87, 0.47, 0.17},
	{1.44, 0.80, 0.30}
};

void calculate_charge(int st, int et, const double rates[],
	double& charge, int& day_time_spent, int& evening_time_spent, int& night_time_spent)
{
	const int day_time = 8 * 60, evening_time = 18 * 60, night_time = 22 * 60;
	if (st < day_time) {
		if (et < day_time) {
			night_time_spent += et - st;
			charge += rates[2] * (et - st);
			st = et;
		}
		else {
			night_time_spent += day_time - st;
			charge += rates[2] * (day_time - st);
			st = day_time;
		}
	}
	else if (st < evening_time) {
		if (et < evening_time) {
			day_time_spent += et - st;
			charge += rates[0] * (et - st);
			st = et;
		}
		else {
			day_time_spent += evening_time - st;
			charge += rates[0] * (evening_time - st);
			st = evening_time;
		}
	}
	else if (st < night_time) {
		if (et < night_time) {
			evening_time_spent += et - st;
			charge += rates[1] * (et - st);
			st = et;
		}
		else {
			evening_time_spent += night_time - st;
			charge += rates[1] * (night_time - st);
			st = night_time;
		}
	}
	else {
		night_time_spent += et - st;
		charge += rates[2] * (et - st);
		st = et;
	}
	if (st != et) {
		if (st == day_time) {
			if (et < evening_time) {
				day_time_spent += et - st;
				charge += rates[0] * (et - st);
			}
			else {
				day_time_spent += evening_time - st;
				charge += rates[0] * (evening_time - st);
				st = evening_time;
			}
		}
		if (st == evening_time) {
			if (et < night_time) {
				evening_time_spent += et - st;
				charge += rates[1] * (et - st);
			}
			else {
				evening_time_spent += night_time - st;
				charge += rates[1] * (night_time - st);
				st = night_time;
			}
		}
		if (st == night_time) {
			night_time_spent += et - st;
			charge += rates[2] * (et - st);
		}
	}
}

int main()
{
	while (true) {
		char step;
		const int nr_numbers_chars = 8;
		char number[nr_numbers_chars + 1];
		int sh, sm, eh, em;
		scanf("%c", &step);
		if (step == '#') {
			getchar();
			break;
		}
		scanf("%s %d %d %d %d", number, &sh, &sm, &eh, &em);
		getchar();
		int s = step - 'A', st = sh * 60 + sm, et = eh * 60 + em;
		double charge = 0.0;
		int day_time_spent = 0, evening_time_spent = 0, night_time_spent = 0;
		if (st >= et) {
			calculate_charge(st, 1440, charging_rates[s],
				charge, day_time_spent, evening_time_spent, night_time_spent);
			calculate_charge(0, et, charging_rates[s],
				charge, day_time_spent, evening_time_spent, night_time_spent);
		}
		else
			calculate_charge(st, et, charging_rates[s],
				charge, day_time_spent, evening_time_spent, night_time_spent);
		printf("%10s%6d%6d%6d%3c%8.2lf\n", number, day_time_spent, evening_time_spent, night_time_spent, step, charge);
	}
	return 0;
}

