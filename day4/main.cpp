#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int checkDir(vector<vector<char> > mainMatrix, pair<int, int> coord)
{
	int max_size_v = mainMatrix.size();
	int max_size_h = mainMatrix[0].size();
	if ((coord.first - 1 < 0) || (coord.first + 1 >= max_size_v) ||
	    (coord.second - 1 < 0) || (coord.second + 1 >= max_size_h)) {
		return 0;
	}

	int check_1 = 0, check_2 = 0;
	if (mainMatrix[coord.first][coord.second] == 'A') {
		if ((mainMatrix[coord.first - 1][coord.second - 1] == 'M') &&
		    (mainMatrix[coord.first + 1][coord.second + 1] == 'S')) {
			check_1 |= 1;
		}
		else if ((mainMatrix[coord.first + 1][coord.second + 1] == 'M') &&
		    (mainMatrix[coord.first - 1][coord.second - 1] == 'S')) {
			check_1 |= 1;
		}

		if ((mainMatrix[coord.first + 1][coord.second - 1] == 'M') &&
		    (mainMatrix[coord.first - 1][coord.second + 1] == 'S')) {
			check_2 |= 1;
		}
		else if ((mainMatrix[coord.first - 1][coord.second + 1] == 'M') &&
		    (mainMatrix[coord.first + 1][coord.second - 1] == 'S')) {
			check_2 |= 1;
		}
	}

	return (check_1 && check_2);
}

int main(int argc, char *argv[])
{
	cout << "AOC day 3" << endl;

	std::ifstream file("./day4.txt");
	string line;
	vector<vector<char> > mainMatrix;
	int count = 0;
	while (getline(file, line)) {
		//cout << line << endl;
		vector<char> line_vec;
		for (char c : line)
			line_vec.push_back(c);
		mainMatrix.push_back(line_vec);
	}
	//cout << endl;
	pair<int, int> coord;
	int max_size_v = mainMatrix.size();
	int max_size_h = mainMatrix[0].size();
	for (int vert_coord = 0; vert_coord < max_size_v; vert_coord++) {
		for (int horz_coord = 0; horz_coord < max_size_h;
		     horz_coord++) {
			coord.first = vert_coord;
			coord.second = horz_coord;
			int xmas = 0;
			xmas += checkDir(mainMatrix, coord);
			//cout << xmas;
			count += xmas;
		}
		//cout << endl;
	}
	cout << "count: " << count << endl;
}
