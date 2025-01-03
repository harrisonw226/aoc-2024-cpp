#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

using namespace std;

void printVec(vector<uint64_t> vec)
{
	cout << "vector: ";
	for (int i : vec) {
		cout << i << " ";
	}
	cout << endl;
}

void test()
{
	for (uint16_t i = 0; i < (2 << 4); i++) {
		uint16_t temp = i;
		for (uint8_t j = 0; j < 16; j++) {
			if (temp & 1) {
				cout << "+";
			} else {
				cout << "x";
			}
			temp = temp >> 1;
		}
		cout << endl;
	}
}

uint64_t checkValid(vector<uint64_t> vec)
{
	uint64_t goal = vec[0];
	vector<int> numbers(vec.begin() + 1, vec.end());
	int length = numbers.size();
	//cout << "goal: " << goal;
	//cout << " length: " << length << endl;
	if (length > 15)
		cout << length << endl;
	for (uint16_t i = 0; i < (2 << (length - 2)); i++) {
		uint16_t temp = i;
		uint64_t value = numbers[0];
		for (uint8_t j = 0; j < length - 1; j++) {
			if (temp & 1) {
				//cout << value << "+" << numbers[j + 1] << endl;
				value += numbers[j + 1];
			} else {
				//cout << value << "x" << numbers[j + 1] << endl;
				value *= numbers[j + 1];
			}
			temp = temp >> 1;
		}
		//cout << "final value: " << value << endl;
		if (value == goal){
			//cout << "found goal" << endl;
			return goal;
		}
	}

	return 0;
}

int main(int argc, char *argv[])
{
	cout << "AOC day 7" << endl;

	std::ifstream file("./day7.txt");
	string line;
	string delim = " ";
	uint64_t count = 0;	
	while (getline(file, line)) {
		uint64_t temp, prev, value;
		vector<uint64_t> values;
		prev = 0;
		temp = 0;
		while ((temp = line.find(delim, temp + 1)) != string::npos) {
			value = stol(line.substr(prev, temp));
			values.push_back(value);
			prev = temp;
		}
		value = stol(line.substr(prev, temp));
		values.push_back(value);
		//printVec(values);
		count += checkValid(values);
	}
	cout << "final count: " << count << endl;
}
