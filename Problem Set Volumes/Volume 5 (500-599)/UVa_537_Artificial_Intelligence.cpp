
/*
	UVa 537 - Artificial Intelligence?

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_537_Artificial_Intelligence.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
using namespace std;

enum {p_field = 0x1, u_field = 0x2, i_field = 0x4}; // field types

int parse_data_field(const char* p, double& value)
{
	char concept, prefix;
	sscanf(p, "%c=%lf%c", &concept, &value, &prefix);
	int field = (concept == 'P') ? p_field : ((concept == 'U') ? u_field : i_field);
	switch (prefix) {
	case 'm': // milli
		value /= 1000.0; break;
	case 'k': // kilo
		value *= 1000.0; break;
	case 'M': // mega
		value *= 1000000.0; break;
	default: // no prefix
		break;
	}
	return field;
}

inline double remove_minus_zero(double d)
{
	return (d == -0.0) ? 0.0 : d;
}

int main(int /* argc */, char** /* argv */)
{
	string line;
	getline(cin, line);
	istringstream iss(line);
	int nr_cases; // number of test cases
	iss >> nr_cases;
	for (int c = 0; c < nr_cases; c++) {
		getline(cin, line);
		int nr_found = 0, found_fields = 0;
		double p_value, u_value, i_value;
		for (const char* p = line.c_str(); *p; p++)
			if (*p == '=') {
				double value;
				int field = parse_data_field(p - 1, value);
				switch (field) {
				case p_field:
					p_value = value; break;
				case u_field:
					u_value = value; break;
				case i_field:
					i_value = value; break;
				}
				found_fields |= field;
				if (++nr_found == 2)
					break;
			}
		printf("Problem #%d\n", c + 1);
		if (!(found_fields & p_field))
			printf("P=%.2fW\n\n", remove_minus_zero(u_value * i_value));
		else if (!(found_fields & u_field))
			printf("U=%.2fV\n\n", remove_minus_zero(p_value / i_value));
		else
			printf("I=%.2fA\n\n", remove_minus_zero(p_value / u_value));
	}
	return 0;
}

