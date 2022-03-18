#pragma once
#include <string>
#include <vector>

using namespace std;

struct Bank {

	string name, code, address, type;

	vector<string> servicesList;
};

struct Banks {

	vector<Bank> list;
};