
/*
	UVa 142 - Mouse Clicks

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_142_Mouse_Clicks.cpp
*/

#include <iostream>
#include <iomanip>
using namespace std;

struct icon_region { // icon or region
	char ir_; // 'I' or 'R'
	int icon_n_; // icon number, negative if obscured by a region
	char region_l_; // region label
	int top_, left_, bottom_, right_;
};

int main()
{
	const int nr_regions_max = 25, nr_icons_max = 50;
	icon_region icon_regions[nr_regions_max + nr_icons_max];
	const int max_icon_distance = 2 * 500 * 500;
	int icon_distances[nr_icons_max + 1]; // square of distances
	int nr_icon_regions = 0;
	int icon_n = 1;
	char region_l = 'A';
	bool first_mouse_click = true;
	while (true) {
		char c;
		cin >> c;
		if (c == '#')
			break;
		if (c == 'I') {
			icon_region& ir = icon_regions[nr_icon_regions];
			ir.ir_ = c;
			ir.icon_n_ = icon_n++;
			cin >> ir.top_ >> ir.left_;
			nr_icon_regions++;
		}
		else if (c == 'R') {
			icon_region& ir = icon_regions[nr_icon_regions];
			ir.ir_ = c;
			ir.region_l_ = region_l++;
			cin >> ir.top_ >> ir.left_ >> ir.bottom_ >> ir.right_;
			nr_icon_regions++;
		}
		else { // 'M'
			if (first_mouse_click) {
				first_mouse_click = false;
				// see if an icon is obscured by a region
				for (int irg = 0; irg < nr_icon_regions; irg++) {
					icon_region& rg = icon_regions[irg];
					if (rg.ir_ == 'R') {
						for (int iic = 0; iic < nr_icon_regions; iic++) {
							icon_region& ic = icon_regions[iic];
							if (ic.ir_ == 'I' && ic.icon_n_ > 0 &&
								ic.top_ >= rg.top_ && ic.top_ <= rg.bottom_ && ic.left_ >= rg.left_ && ic.left_ <= rg.right_)
								ic.icon_n_ = -ic.icon_n_; // icon is obscured by a region
						}
					}
				}
			}
			int top, left;
			int selected = -1, min_d = max_icon_distance;
			cin >> top >> left;
			for (int iir = nr_icon_regions - 1; iir >= 0; iir--) {
				icon_region& ir = icon_regions[iir];
				if (ir.ir_ == 'R') {
					if (top >= ir.top_ && top <= ir.bottom_ && left >= ir.left_ && left <= ir.right_) {
						selected = iir; break;
					}
				}
				else {
					if (ir.icon_n_ > 0 && top == ir.top_ && left == ir.left_) {
						selected = iir; break;
					}
					else
						if (ir.icon_n_ < 0) // an obscured icon should not be considered
							icon_distances[-ir.icon_n_] = max_icon_distance;
						else {
							icon_distances[ir.icon_n_] = (top - ir.top_) * (top - ir.top_) + (left - ir.left_) * (left - ir.left_);
							if (icon_distances[ir.icon_n_] < min_d)
								min_d = icon_distances[ir.icon_n_];
						}
				}
			}
			if (selected != -1) {
				icon_region& ir = icon_regions[selected];
				if (ir.ir_ == 'R')
					cout << ir.region_l_ << endl;
				else
					cout << setfill(' ') << setw(3) << ir.icon_n_ << endl;
			}
			else {
				for (int ii = 1; ii <= icon_n; ii++)
					if (icon_distances[ii] == min_d)
						cout << setfill(' ') << setw(3) << ii;
				cout << endl;
			}
		}
	}
	return 0;
}

