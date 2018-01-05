
/*
	UVa 10371 - Time Zones

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10371_Time_Zones.cpp

	from Waterloo ACM Programming Contest September 28, 2002, Problem E
		(http://acm.student.cs.uwaterloo.ca/~acm00/020928/data/)
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

struct time_zone {
	const char*  abbreviation_;
	int offset_; // in minutes
};

int compare_time_zone(const void* i, const void* j)
{
	const time_zone *ti = reinterpret_cast<const time_zone*>(i), *tj = reinterpret_cast<const time_zone*>(j);
	return strcmp(ti->abbreviation_, tj->abbreviation_);
}

time_zone time_zones[] = {
	{"UTC", 0},
	{"GMT", 0},
	{"BST", 60},
	{"IST", 60},
	{"WET", 0},
	{"WEST", 60},
	{"CET", 60},
	{"CEST", 120},
	{"EET", 120},
	{"EEST", 180},
	{"MSK", 180},
	{"MSD", 240},
	{"AST", -240},
	{"ADT", -180},
	{"NST", -210},
	{"NDT", -150},
	{"EST", -300},
	{"EDT", -240},
	{"CST", -360},
	{"CDT", -300},
	{"MST", -420},
	{"MDT", -360},
	{"PST", -480},
	{"PDT", -420},
	{"HST", -600},
	{"AKST", -540},
	{"AKDT", -480},
	{"AEST", 600},
	{"AEDT", 660},
	{"ACST", 570},
	{"ACDT", 630},
	{"AWST", 480}
};

int convert_time(int minute, const char* abbreviation, bool utc)
{
	time_zone tz;
	tz.abbreviation_ = abbreviation;
	time_zone* ptz = reinterpret_cast<time_zone*>(bsearch(&tz,
		time_zones, sizeof(time_zones) / sizeof(time_zone), sizeof(time_zone), compare_time_zone));
	if (utc)
		minute -= ptz->offset_;
	else
		minute += ptz->offset_;
	if (minute >= 60 * 24)
		minute -= 60 * 24;
	else if (minute < 0)
		minute += 60 * 24;
	return minute;
}


int main()
{
	qsort(time_zones, sizeof(time_zones) / sizeof(time_zone), sizeof(time_zone), compare_time_zone);
	const char *noon = "noon", *midnight = "midnight", *am = "a.m.", *pm = "p.m.";
	int N;
	scanf("%d", &N);
	while (N--) {
		char s[8], t[8];
		scanf("%s", s);
		int hour, minute;
		if (!strcmp(s, noon))
			minute = 60 * 12;
		else if (!strcmp(s, midnight))
			minute = 0;
		else {
			sscanf(s, "%d:%d", &hour, &minute);
			if (hour != 12)
				minute += hour * 60;
			scanf("%s", s);
			if (!strcmp(s, pm))
				minute += 60 * 12;
		}
		scanf("%s %s", s, t);
		minute = convert_time(minute, s, true);
		minute = convert_time(minute, t, false);
		if (!minute)
			puts(midnight);
		else if (minute == 60 * 12)
			puts(noon);
		else {
			hour = minute / 60;
			minute %= 60;
			if (hour >= 12)
				printf("%d:%02d p.m.\n", ((hour > 12) ? hour - 12 : hour), minute);
			else {
				printf("%d:%02d a.m.\n", ((hour) ? hour : 12), minute);
			}
		}
	}
	return 0;
}

