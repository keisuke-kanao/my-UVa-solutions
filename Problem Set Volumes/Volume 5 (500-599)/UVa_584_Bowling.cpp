
/*
	UVa 584 - Bowling

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_584_Bowling.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

const int nr_pins = 10, nr_frames_max = 10;
enum {bonus_none, bonus_strike, bonus_spare};

struct frame {
	int first_score_, second_score_;
	int bonus_;
};

int main()
{
	while (true) {
		string s;
		getline(cin, s);
		if (s[0] == 'G') // Game Over
			break;
		istringstream iss(s);
		frame frames[nr_frames_max + 1];
		for (int i = 0; i <= nr_frames_max; i++) {
			frames[i].first_score_ = -1;
			frames[i].second_score_ = 0;
			frames[i].bonus_ = bonus_none;
		}
		int nr_frames = 0;
		char c;
		while (iss >> c) {
			switch (c) {
			case 'X': // strike
				if (nr_frames == nr_frames_max) { // additional rolls after the tenth frame
					if (frames[nr_frames].first_score_ == -1) {
						frames[nr_frames].first_score_ = nr_pins;
						if (frames[nr_frames - 1].bonus_ == bonus_spare) // spare in the tenth frame
							nr_frames++;
					}
					else { // strike in the tenth frame
						frames[nr_frames].second_score_ = nr_pins;
						nr_frames++;
					}
				}
				else {
					frames[nr_frames].first_score_ = nr_pins;
					frames[nr_frames].bonus_ = bonus_strike;
					nr_frames++;
				}
				break;
			case '/': // spare
				frames[nr_frames].second_score_ = nr_pins - frames[nr_frames].first_score_;
				if (nr_frames < nr_frames_max)
					frames[nr_frames].bonus_ = bonus_spare;
				nr_frames++;
				break;
			default:
				if (frames[nr_frames].first_score_ == -1)
					frames[nr_frames].first_score_ = c - '0';
				else {
					frames[nr_frames].second_score_ = c - '0';
					nr_frames++;
				}
				break;
			}
		}
		int score = 0;
		for (int i = 0; i < nr_frames_max; i++) {
			score += frames[i].first_score_ + frames[i].second_score_;
			switch (frames[i].bonus_) {
			case bonus_strike:
				if (frames[i + 1].bonus_ == bonus_strike)
					score += frames[i + 1].first_score_ + frames[i + 2].first_score_;
				else
					score += frames[i + 1].first_score_ + frames[i + 1].second_score_;
				break;
			case bonus_spare:
				score += frames[i + 1].first_score_;
				break;
			default:
				break;
			}
		}
		cout << score << endl;
	}
	return 0;
}

