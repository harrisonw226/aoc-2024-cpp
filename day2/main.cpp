#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

int mag(int value)
{
	if (value < 0)
		return -value;
	else
		return value;
}

int increasing(int value1, int value2)
{
	if (value2 == value1)
		return 0;
	return (value2 - value1) / mag(value2 - value1);
}

using namespace std;
int main(int argc, char *argv[])
{
	cout << "AOC day 2" << endl;

	std::ifstream file("./day2.txt");
	string line;
	int increasing_flag;
	int min = 1;
	int max = 3;
	int count = 0;
	string delim = " ";

	while (getline(file, line)) {
		int temp, prev, level;
		vector<int> levels;
		prev = 0;
		temp = 0;

		while ((temp = line.find(delim, temp + 1)) != string::npos) {
			level = stoi(line.substr(prev, temp));
			levels.push_back(level);
			prev = temp;
		}
		level = stoi(line.substr(prev, temp));
		levels.push_back(level);

		increasing_flag = increasing(levels[0], levels[1]);
		prev = levels[0];
		int failed = 0;
		for (int i = 1; i < levels.size(); i++) {
			level = levels[i];
			if (increasing(prev, level) == 0) {
				failed = 1;
				continue;
			}

			if (increasing(prev, level) != increasing_flag) {
				failed = 1;
				continue;
			}

			if (mag(level - prev) > 3) {
				failed = 1;
				continue;
			}

			prev = level;
		}
		if (!failed)
			count += 1;
	}
	cout << count << endl;
}
