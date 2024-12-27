#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

map<int, vector<int> > page_order_map;

void printVector(vector<int> vec)
{
	for (int i : vec) {
		cout << i << " ";
	}
	cout << endl;
}

void addToMap(int before_pg, int after_pg)
{
	if (auto search = page_order_map.find(before_pg);
	    search != page_order_map.end()) {
		search->second.push_back(after_pg);
		cout << "added to vector" << endl;
	} else {
		page_order_map.insert(
			pair<int, vector<int> >(before_pg, { after_pg }));
		cout << "added to map" << endl;
	}
}
vector<int> populatePageList(string line)
{
	string delim = ",";
	int page, prev = 0, temp = 0;
	vector<int> pages;
	while ((temp = line.find(delim, temp + 1)) != string::npos) {
		page = stoi(line.substr(prev, temp));
		pages.push_back(page);
		prev = temp + 1;
	}
	page = stoi(line.substr(prev, temp));
	pages.push_back(page);
	return pages;
}

int checkValidPage(int current_page, vector<int> pages_before)
{
	int valid = 0;
	map<int, vector<int> >::iterator search;
	vector<int> vec;
	if (search = page_order_map.find(current_page);
	    search == page_order_map.end()) {
		return 1;
	}
	vec = search->second;

	for (int page : vec) {
		if (find(pages_before.begin(), pages_before.end(), page) !=
		    pages_before.end()) {
			return 0;
		}
	}
	return 1;
}

int checkValidList(vector<int> page_list)
{
	for (int current_page_idx = 0; current_page_idx < page_list.size();
	     current_page_idx++) {
		int current_page = page_list[current_page_idx];
		vector<int> pages_before(page_list.begin(),
					 page_list.begin() + current_page_idx);
		cout << "index: " << current_page_idx
		     << " valid: " << checkValidPage(current_page, pages_before)
		     << endl;
		if (!checkValidPage(current_page, pages_before))
			return 0;
	}
	return 1;
}

int main(int argc, char *argv[])
{
	cout << "AOC day 3" << endl;

	std::ifstream file("./day5.txt");
	string line;
	int before_pg, after_pg;
	int stage = 0;
	int sum = 0;
	while (getline(file, line)) {
		cout << "line: " << line << endl;
		if (line == "") {
			stage++;
			continue;
		}
		switch (stage) {
		case 0:
			before_pg = stoi(line.substr(0, line.length() / 2));
			after_pg = stoi(line.substr((line.length() / 2) + 1));
			addToMap(before_pg, after_pg);
			break;
		case 1:
			vector pages = populatePageList(line);
			cout << "vector: ";
			printVector(pages);
			int valid = checkValidList(pages);
			if (valid){
				sum += pages[pages.size()/2];
			}
			break;
		}
	}
	cout << "sum: " << sum << endl;
}