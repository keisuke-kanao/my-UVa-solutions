
/*
	1.6.6 Interpreter
	PC/UVa IDs: 110106/10033, Popularity: B, Success rate: low Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10033_Interpreter.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

const int number_of_registers = 10, ram_size = 1000, three_digit_integer_max = 999;

int execute_program(int ram[])
{
	int location = 0, registers[number_of_registers];
	for (int i = 0; i < number_of_registers; i++)
		registers[i] = 0;
	for (int instructions = 0; ; instructions++) {
		int first_digit = ram[location] / 100, second_digit = (ram[location] / 10) % 10, third_digit = ram[location] % 10;
		switch (first_digit) {
		case 1: // 100 - halt
			return instructions + 1;
		case 2: // 2dn - set register d to n (between 0 and 9)
			registers[second_digit] = third_digit;
			location++;
			break;
		case 3: // 3dn - add n to register d
			registers[second_digit] += third_digit;
			registers[second_digit] %= three_digit_integer_max + 1;
			location++;
			break;
		case 4: // 4dn - multiply register d by n
			registers[second_digit] *= third_digit;
			registers[second_digit] %= three_digit_integer_max + 1;
			location++;
			break;
		case 5: // 5ds - set register d to the value of register s
			registers[second_digit] = registers[third_digit];
			location++;
			break;
		case 6: // 6ds - add the value of register s to register d
			registers[second_digit] += registers[third_digit];
			registers[second_digit] %= three_digit_integer_max + 1;
			location++;
			break;
		case 7: // 7ds - multiply register d by the value of register s
			registers[second_digit] *= registers[third_digit];
			registers[second_digit] %= three_digit_integer_max + 1;
			location++;
			break;
		case 8: // 8da - set register d to the value in RAM whose address is in register a
			registers[second_digit] = ram[registers[third_digit]];
			location++;
			break;
		case 9: // 9sa - set the value in RAM whose address is in register a to that of register s
			ram[registers[third_digit]] = registers[second_digit];
			location++;
			break;
		case 0: // 0ds - goto the location in register d unless register s contains 0
			if (registers[third_digit])
				location = registers[second_digit];
			else
				location++;
			break;
		}
	}
}

int main(int /* argc */, char** /* argv */)
{
	string line;
	istringstream iss;
	int ram_location, ram[ram_size];

	getline(cin, line);
	iss.str(line);
	int cases;
	iss >> cases;
	iss.clear();
	if (cases)
		getline(cin, line); // skip the first blank line
	ram_location = 0;
	for (int i = 0; i < ram_size; i++)
		ram[i] = 0;
	while (cases) {
		if (!getline(cin, line) || line.empty()) { // end of intput or a blank line
			if (ram_location) // execute the program and print the number of instructiones executed
				cout << execute_program(ram) << endl;
			ram_location = 0;
			for (int i = 0; i < ram_size; i++)
				ram[i] = 0;
			if (--cases)
				cout << endl; // separate the output of two consecutive cases by a blank line
		}
		else { // read instructions
			iss.str(line);
			iss >> ram[ram_location++];
			iss.clear();
		}
	}
	return 0;
}

