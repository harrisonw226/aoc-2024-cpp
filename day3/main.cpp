#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>

using namespace std;
int main(int argc, char *argv[])
{
	cout << "AOC day 3" << endl;

	std::ifstream file("./day3.txt");
	string line;
	int num1 = 0, num2 = 0, total = 0;
	regex str_expr_mul("(mul\\()[0-9]{1,3}\\,[0-9]{1,3}\\)");
	regex str_expr_num("[0-9]{1,3}");
	while (getline(file, line)) {
		cout << line << endl;
		for (smatch m; regex_search(line, m, str_expr_mul);) {
			string mul_str = m.str();
			line = m.suffix();
			smatch num_match;
			regex_search(mul_str, num_match, str_expr_num);
			int num1 = stoi(num_match.str());
			mul_str = num_match.suffix();
			regex_search(mul_str, num_match, str_expr_num);
			int num2 = stoi(num_match.str());
			total += num1 * num2;
			cout << num1 << " " << num2 << " " << num1 * num2 << " "
			     << total << endl;
		}
	}
	cout << "total: " << total << endl;
}
