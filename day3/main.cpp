#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

enum FLAG {
	flag_dont,
	flag_do,
};

enum STATES {
	state_default,
	state_m,
	state_u,
	state_l,
	state_b1,
	state_n1,
	state_c,
	state_n2,
	state_b2,
	state_d,
	state_o,
	state_n,
	state_ap,
	state_t,
	state_b3,
	state_b4,
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

ACTION stateMachine(char c, STATES *state, FLAG *flag)
{
	switch (*flag) {
	case flag_do:
		switch (*state) {
		case state_default:
			if (c == 'm') {
				*state = state_m;
				return stay;
			} else if (c == 'd') {
				*state = state_d;
				return stay;
			} else {
				return error;
			}
			break;
		case state_d:
			if (c == 'd') {
				*state = state_o;
				return next;
			} else {
				*state = state_default;
				return error;
			}
			break;
		case state_o:
			if (c == 'o') {
				*state = state_n;
				return next;
			} else {
				*state = state_default;
				return error;
			}
			break;
		case state_n:
			if (c == 'n') {
				*state = state_ap;
				return next;
			} else {
				*state = state_default;
				return error;
			}
			break;
		case state_ap:
			if (c == '\'') {
				*state = state_t;
				return next;
			} else {
				*state = state_default;
				return error;
			}
			break;
		case state_t:
			if (c == 't') {
				*state = state_b3;
				return next;
			} else {
				*state = state_default;
				return error;
			}
			break;
		case state_b3:
			if (c == '(') {
				*state = state_b4;
				return next;
			} else {
				*state = state_default;
				return error;
			}
			break;
		case state_b4:
			if (c == ')') {
				*state = state_default;
				*flag = flag_dont;
				return next;
			} else {
				*state = state_default;
				return error;
			}
			break;
		case state_m:
			if (c == 'm') {
				*state = state_u;
				return next;
			} else {
				*state = state_default;
				return error;
			}
			break;
		case state_u:
			if (c == 'u') {
				*state = state_l;
				return next;
			} else {
				*state = state_default;
				return error;
			}
			break;
		case state_l:
			if (c == 'l') {
				*state = state_b1;
				return next;
			} else {
				*state = state_default;
				return error;
			}
			break;
		case state_b1:
			if (c == '(') {
				*state = state_n1;
				return next;
			} else {
				*state = state_default;
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
				*state = state_default;
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
				*state = state_default;
				return error;
			}
			break;
		case state_b2:
			if (c == ')') {
				*state = state_m;
				return success;
			} else {
				*state = state_default;
				return error;
			}
			break;
		}
		break;
	case flag_dont:
		switch (*state) {
		case state_default:
			if (c == 'd') {
				*state = state_d;
				return stay;
			} else {
				return error;
			}
			break;
		case state_d:
			if (c == 'd') {
				*state = state_o;
				return next;
			} else {
				*state = state_default;
				return error;
			}
			break;
		case state_o:
			if (c == 'o') {
				*state = state_b3;
				return next;
			} else {
				*state = state_default;
				return error;
			}
			break;
		case state_b3:
			if (c == '(') {
				*state = state_b4;
				return next;
			} else {
				*state = state_default;
				return error;
			}
			break;
		case state_b4:
			if (c == ')') {
				*state = state_default;
				*flag = flag_do;
				return next;
			} else {
				*state = state_default;
				return error;
			}
		default:
			*state = state_default;
			return next;
		}
	}
	return error;
}

using namespace std;
int main(int argc, char *argv[])
{
	cout << "AOC day 3" << endl;

	std::ifstream file("./day3.test");
	string line;
	STATES state = state_m;
	ACTION action;
	FLAG flag = flag_do;
	int num1 = 0, num2 = 0, total = 0;
	while (getline(file, line)) {
		cout << line << endl;
		for (char c : line) {
			while ((action = stateMachine(c, &state, &flag)) ==
			       stay) {
				cout << "char: " << c << " number? "
				     << checkNumber(c) << " state: " << state
				     << " action: " << action
				     << " flag: " << flag << endl;
			}
			cout << "char: " << c << " number? " << checkNumber(c)
			     << " state: " << state << " action: " << action
			     << " flag: " << flag << endl;
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
