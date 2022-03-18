#pragma once
#include <string>

using namespace std;

struct Bank {

	string name, code, address, type;

	string* servicesList = new string[0];

	size_t servicesListLength = 0;
};

struct Banks {

	Bank* list = new Bank[0];

	size_t listLength = 0;
};