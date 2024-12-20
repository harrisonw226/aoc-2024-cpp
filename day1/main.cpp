#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main(int argc, char *argv[])
{
	cout << "AOC day 1" << endl;

	std::ifstream file("./day1.txt");
	string line;
	int first_half, second_half, mag;
	vector<int> vec_1, vec_2;
	mag = 0;
	while (getline(file, line)) {
		vec_1.push_back(stoi(line.substr(0, line.length() / 2)));
		vec_2.push_back(stoi(line.substr(line.length() / 2)));
	}
	sort(vec_1.begin(), vec_1.end());
	sort(vec_2.begin(), vec_2.end());

	for (int i = 0; i < vec_1.size(); i++) {
		first_half = vec_1[i];
		int temp = first_half * count(vec_2.begin(), vec_2.end(), first_half);
		mag += temp;
	}
	cout << mag << endl;
}
