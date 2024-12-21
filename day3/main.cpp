#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

enum STATES {
	state_m,
	state_u,
	state_l,
	state_b1,
	state_n1,
	state_c,
	state_n2,
	state_b2,
};

enum ACTION {
	next,
	stay,
	error,
	success,
	number,
};

int checkNumber(char c)
{
	int output = c - 48;
	if ((output < 0) || (output > 9)) {
		return -1;
	}
	return output;
}

ACTION stateMachine(char c, STATES *state)
{
	switch (*state) {
	case state_m:
		if (c == 'm') {
			*state = state_u;
			return next;
		}
		return error;
		break;
	case state_u:
		if (c == 'u') {
			*state = state_l;
			return next;
		} else {
			*state = state_m;
			return error;
		}
		break;
	case state_l:
		if (c == 'l') {
			*state = state_b1;
			return next;
		} else {
			*state = state_m;
			return error;
		}
		break;
	case state_b1:
		if (c == '(') {
			*state = state_n1;
			return next;
		} else {
			*state = state_m;
			return error;
		}
		break;
	case state_n1:
		if (checkNumber(c) != -1) {
			*state = state_n1;
			return number;
		} else if (c == ',') {
			*state = state_c;
			return stay;
		} else {
			*state = state_m;
			return error;
		}
		break;
	case state_c:
		if (c == ',') {
			*state = state_n2;
			return next;
		} else {
			*state = state_m;
			return error;
		}
		break;
	case state_n2:
		if (checkNumber(c) != -1) {
			*state = state_n2;
			return number;
		} else if (c == ')') {
			*state = state_b2;
			return stay;
		} else {
			*state = state_m;
			return error;
		}
		break;
	case state_b2:
		if (c == ')') {
			*state = state_m;
			return success;
		} else {
			*state = state_m;
			return error;
		}
		break;
	}
	return error;
}

using namespace std;
int main(int argc, char *argv[])
{
	cout << "AOC day 3" << endl;

	std::ifstream file("./day3.txt");
	string line;
	STATES state = state_m;
	ACTION action;
	int num1 = 0, num2 = 0, total = 0;
	while (getline(file, line)) {
		cout << line << endl;
		for (char c : line) {
			while ((action = stateMachine(c, &state)) == stay) {
				cout << "char: " << c << " number? "
				     << checkNumber(c) << " state: " << state
				     << " action: " << action << endl;
			}
			cout << "char: " << c << " number? " << checkNumber(c)
			     << " state: " << state << " action: " << action
			     << endl;
			if (action == error) {
				num1 = 0;
				num2 = 0;
				continue;
			} else if (state == state_n1 && action == number) {
				num1 *= 10;
				num1 += c - 48;
				cout << "num1: " << num1 << endl;
			} else if (state == state_n2 && action == number) {
				num2 *= 10;
				num2 += c - 48;
				cout << "num2: " << num2 << endl;
			}
			if ((action == success) && (num1 < 1000) &&
			    (num2 < 1000)) {
				cout << "mul: " << num1 * num2 << endl;
				total += num1 * num2;
				num1 = 0;
				num2 = 0;
			}
		}
		cout << "total: " << total << endl;
	}
}
