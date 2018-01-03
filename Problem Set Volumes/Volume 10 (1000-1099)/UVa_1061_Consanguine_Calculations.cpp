
/*
	UVa 1061 - Consanguine Calculations

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1061_Consanguine_Calculations.cpp
*/

#include <cstdio>
#include <cstring>

enum {A_allele, B_allele, O_allele};
enum {A_type, AB_type, B_type, O_type};
enum {Rh_positive, Rh_negative};

const int nr_blood_types = O_type - A_type + 1;

struct blood_types {
	int ctr_;
	bool types_[nr_blood_types];
};

blood_types parent_other_parent[nr_blood_types][nr_blood_types] = {
	{ // A
		{2, {true,	false,	false,	true}},		// A
		{3, {true,	true,	true,	false}},	// AB
		{4, {true,	true, 	true,	true}},		// B
		{2, {true,	false,	false,	true}}		// O
	},
	{ // AB
		{3, {true,	true,	true,	false}},	// A
		{3,	{true,	true,	true,	false}},	// AB
		{3,	{true,	true,	true,	false}},	// B
		{2,	{true,	false,	true,	false}}		// O
	},
	{ // B
		{4, {true,	true, 	true,	true}},		// A
		{3,	{true,	true,	true,	false}},	// AB
		{2,	{false,	false,	true,	true}},		// B
		{2,	{false,	false,	true,	true}},		// O
	},
	{ // O
		{2,	{true,	false,	false,	true}},		// A
		{2, {true,	false,	true,	false}},	// AB
		{2,	{false,	false,	true,	true}},		// B
		{1,	{false,	false,	false,	true}}		// O
	}
};

blood_types parent_child[nr_blood_types][nr_blood_types] = {
	{ // A
		{4, {true,	true,	true,	true}},		// A
		{2,	{false,	true,	true,	false}},	// AB
		{2,	{false,	true,	true,	false}},	// B
		{3,	{true,	false,	true,	true}},		// O
	},
	{ // AB
		{4,	{true,	true,	true,	true}},		// A
		{3,	{true,	true,	true,	false}},	// AB
		{4,	{true,	true,	true,	true}},		// B
		{0,	{false,	false,	false,	false}},	// O
	},
	{ // B
		{2,	{true,	true,	false,	false}},	// A
		{2,	{true,	true,	false,	false}},	// AB
		{4,	{true,	true,	true,	true}},		// B
		{3,	{true,	false,	true,	true}},		// O
	},
	{ // O
		{2,	{true,	true,	false,	false}},	// A
		{0,	{false,	false,	false,	false}},	// AB
		{2,	{false,	true,	true,	false}},	// B
		{3,	{true,	false,	true,	true}},		// O
	}
};

const char* blood_symbols[nr_blood_types] = {"A", "AB", "B", "O"};

void get_blood_type_and_rh_factor(const char* s, int& blood_type, int& rh_factor) {
	int length = strlen(s);
	if (length < 3) {
		switch (s[0]) {
		case 'A':
			blood_type = A_type; break;
			break;
		case 'B':
			blood_type = B_type; break;
			break;
		case 'O':
			blood_type = O_type; break;
			break;
		}
	}
	else
		blood_type = AB_type;
	rh_factor = (s[length - 1] == '+') ? Rh_positive : Rh_negative;
}

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		const int nr_chars_max = 3;
		char parent[nr_chars_max + 1], other_parent[nr_chars_max + 1], child[nr_chars_max + 1];
		scanf("%s %s %s", parent, other_parent, child);
		if (parent[0] == 'E')
			break;
		if (parent[0] == '?') {
			int parent_type, parent_factor, child_type, child_factor;
			get_blood_type_and_rh_factor(other_parent, parent_type, parent_factor);
			get_blood_type_and_rh_factor(child, child_type, child_factor);
			blood_types& bt = parent_child[parent_type][child_type];
			if (bt.ctr_) {
				bool factor_positive_only = parent_factor == Rh_negative && child_factor == Rh_positive;
				printf("Case %d: ", case_nr);
				if (bt.ctr_ > 1 || !factor_positive_only)
					putchar('{');
				for (int i = 0, j = 0; i < nr_blood_types; i++)
					if (bt.types_[i]) {
						if (j++)
							printf(", ");
						if (factor_positive_only)
							printf("%s+", blood_symbols[i]);
						else
							printf("%s+, %s-", blood_symbols[i], blood_symbols[i]);
					}
				if (bt.ctr_ > 1 || !factor_positive_only)
					putchar('}');
				printf(" %s %s\n", other_parent, child);
			}
			else
				printf("Case %d: IMPOSSIBLE %s %s\n", case_nr, other_parent, child);
		}
		else if (other_parent[0] == '?') {
			int parent_type, parent_factor, child_type, child_factor;
			get_blood_type_and_rh_factor(parent, parent_type, parent_factor);
			get_blood_type_and_rh_factor(child, child_type, child_factor);
			blood_types& bt = parent_child[parent_type][child_type];
			if (bt.ctr_) {
				bool factor_positive_only = parent_factor == Rh_negative && child_factor == Rh_positive;
				printf("Case %d: %s ", case_nr, parent);
				if (bt.ctr_ > 1 || !factor_positive_only)
					putchar('{');
				for (int i = 0, j = 0; i < nr_blood_types; i++)
					if (bt.types_[i]) {
						if (j++)
							printf(", ");
						if (factor_positive_only)
							printf("%s+", blood_symbols[i]);
						else
							printf("%s+, %s-", blood_symbols[i], blood_symbols[i]);
					}
				if (bt.ctr_ > 1 || !factor_positive_only)
					putchar('}');
				printf(" %s\n", child);
			}
			else
				printf("Case %d: %s IMPOSSIBLE %s\n", case_nr, parent, child);
		}
		else {
			int parent_type, parent_factor, other_parent_type, other_parent_factor;
			get_blood_type_and_rh_factor(parent, parent_type, parent_factor);
			get_blood_type_and_rh_factor(other_parent, other_parent_type, other_parent_factor);
			blood_types& bt = parent_other_parent[parent_type][other_parent_type];
			bool factor_negative_only = parent_factor == Rh_negative && other_parent_factor == Rh_negative;
			printf("Case %d: %s %s ", case_nr, parent, other_parent);
			if (bt.ctr_ > 1 || !factor_negative_only)
				putchar('{');
			for (int i = 0, j = 0; i < nr_blood_types; i++)
				if (bt.types_[i]) {
					if (j++)
						printf(", ");
					if (factor_negative_only)
						printf("%s-", blood_symbols[i]);
					else
						printf("%s+, %s-", blood_symbols[i], blood_symbols[i]);
					}
			if (bt.ctr_ > 1 || !factor_negative_only)
				puts("}");
			else
				putchar('\n');
		}
	}
	return 0;
}

