
/*
	UVa 645 - File Mapping

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_645_File_Mapping.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct dir {
	const string name_;
	dir* parent_;
	vector<dir*> children_;
	vector<string> files_;

	dir(const string& name, dir* parent) : name_(name), parent_(parent) {}

	~dir()
	{
		for (size_t i = 0, j = children_.size(); i < j; i++)
			delete children_[i];
	}

	void print(int depth)
	{
		for (int d = 0; d < depth; d++)
			cout << "|     ";
		cout << name_ << endl;
		for (size_t i = 0, j = children_.size(); i < j; i++)
			children_[i]->print(depth + 1);
		sort(files_.begin(), files_.end());
		for (size_t i = 0, j = files_.size(); i < j; i++) {
			for (int d = 0; d < depth; d++)
				cout << "|     ";
			cout << files_[i] << endl;
		}
	}
};

int main()
{
	for (int ds = 1; ; ds++) {
		string s;
		cin >> s;
		if (s == "#")
			break;
		if (ds > 1)
			cout << endl;
		dir* root = new dir("ROOT", NULL);
		dir* current = root;
		while (s != "*") {
			switch (s[0]) {
			case 'd':
			{
				dir* child = new dir(s, current);
				current->children_.push_back(child);
				current = child;
			}
				break;
			case 'f':
				current->files_.push_back(s);
				break;
			case ']':
				current = current->parent_;
				break;
			}
			cin >> s;
		}
		cout << "DATA SET " << ds << ":\n";
		root->print(0);
		delete root;
	}
	return 0;
}

