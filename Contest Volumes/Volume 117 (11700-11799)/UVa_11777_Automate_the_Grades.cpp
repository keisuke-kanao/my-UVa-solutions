
/*
	UVa 11777 - Automate the Grades

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_11777_Automate_the_Grades.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int t;
	cin >> t;
	for (int case_nr = 1; case_nr <= t; case_nr++) {
		const int nr_class_tests = 3;
		int term_1, term_2, final, attendance, class_tests[nr_class_tests];
		cin >> term_1 >> term_2 >> final >> attendance >> class_tests[0] >> class_tests[1] >> class_tests[2];
		if (class_tests[0] > class_tests[1])
			swap(class_tests[0], class_tests[1]);
		if (class_tests[1] > class_tests[2])
			swap(class_tests[1], class_tests[2]);
		if (class_tests[0] > class_tests[1])
			swap(class_tests[0], class_tests[1]);
		int total_marks = term_1 + term_2 + final + attendance + (class_tests[1] + class_tests[2]) / 2;
		char grade;
		if (total_marks >= 90)
			grade = 'A';
		else if (total_marks >= 80)
			grade = 'B';
		else if (total_marks >= 70)
			grade = 'C';
		else if (total_marks >= 60)
			grade = 'D';
		else
			grade = 'F';
		cout << "Case " << case_nr << ": " << grade << endl;
	}
	return 0;
}

