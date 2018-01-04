
/*
	UVa 139 - Telephone Tangles

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_139_Telephone_Tangles.cpp
*/

#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_chars_number = 15, nr_chars_locality = 25, nr_chars_max = 1023;

struct telephone_code {
	int code_length_;
	char code_[nr_chars_number + 1];
	char locality_[nr_chars_locality + 1];
	double cost_;
};

int main()
{
	vector<telephone_code> telephone_codes;
	while (true) {
		char s[nr_chars_max + 1];
		gets(s);
		if (!strcmp(s, "000000"))
			break;
		telephone_code tc;
		char* p = strchr(s, ' ');
		*p++ = '\0';
		strcpy(tc.code_, s);
		tc.code_length_ = strlen(tc.code_);
		char *q = strchr(p, '$');
		*q++ = '\0';
		strcpy(tc.locality_, p);
		sscanf(q, "%lf", &tc.cost_);
		tc.cost_ /= 100.0;
		telephone_codes.push_back(tc);
	}
	int nr_tc_codes = static_cast<int>(telephone_codes.size());
	while (true) {
		char number[nr_chars_number + 1];
		scanf("%s", number);
		if (number[0] == '#')
			break;
		int duration;
		scanf("%d", &duration);
		int tci = -1;
		if (number[0] == '0') {
			for (tci = 0; tci < nr_tc_codes; tci++)
				if (!strncmp(number, telephone_codes[tci].code_, telephone_codes[tci].code_length_)) {
					int length = strlen(&number[telephone_codes[tci].code_length_]);
					if (length < 4)
						continue;
					if (telephone_codes[tci].code_[1] == '0') {
						if (length <= 10)
							break;
					}
					else { // STD
						if (length <= 7)
							break;
					}
				}
		}
		if (tci == -1)
			printf("%-15s %-5s%30s%5d%6.2lf%7.2lf\n",
				number, "Local", number, duration, 0.0, 0.0);
		else if (tci < nr_tc_codes)
			printf("%-15s %-25s%10s%5d%6.2lf%7.2lf\n",
				number, telephone_codes[tci].locality_,
				&number[telephone_codes[tci].code_length_], duration,
				telephone_codes[tci].cost_, telephone_codes[tci].cost_ * duration);
		else
			printf("%-15s %-35s%5d%13.2lf\n", number, "Unknown", duration, -1.0);
	}
	return 0;
}

